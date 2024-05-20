#include "play_state.h"
#include <iostream>

#include "engine/engine_common.h"



PlayState::PlayState(std::shared_ptr<Context> context)
  : GameState(std::move(context)),
    passport_(0), background_(ResourceManager::GetInstance().GetTexture("bg")) {

  auto& resource_manager = ResourceManager::GetInstance();
  auto& font = resource_manager.GetFont("gothic");
  auto& player_texture = resource_manager.GetTexture("tank");

  player_ = std::make_unique<Player>(player_texture, player_size);
  text_ = std::move(Text(font, "Searching for server...", {400.f, 300.f}));
  text_.SetVisible(true);


//   fake player to test collision
  auto& other_player = other_players_[5];
  other_player = std::make_unique<Player>(player_texture, player_size);
  other_player->SetPosition({400, 400});
  objects_.push_back(std::move(other_player));


  kill_server_btn_ = std::move(Button(font, "Kill Server", {{10.f,540.f}, {300.f,50.f}}));
  auto& wall_texture = resource_manager.GetTexture("wall");

  // TODO: generate walls for host and send other players
  GenerateWalls(wall_texture, objects_, 6);

}

void PlayState::Update(float delta_time) {
  using sfk = sf::Keyboard::Key;
  auto& input = GetInputManager();
  auto &networker = GetContext()->network_manager;
  if (text_.GetVisible()) {
    auto servers = networker->GetAvailableServer();
    if (!servers.empty()){
      ServerAddress server = servers[0];
      networker->Connect(server.host, server.port);
      text_.SetVisible(false);
    }
  }else if(!(server_accepted_connection_.load())){
    Message<GameEventType> msg;
    msg.header.id = GameEventType::ClientRequestConnect;
    networker->Send(msg);
  }else{

    static int A = 0, D = 0, W = 0, S = 0;
    A = std::min(1, int(input.IsKeyPressed(sfk::A)) + A) - input.IsKeyReleased(sfk::A);
    D = std::min(1, int(input.IsKeyPressed(sfk::D)) + D) - input.IsKeyReleased(sfk::D);
    W = std::min(1, int(input.IsKeyPressed(sfk::W)) + W) - input.IsKeyReleased(sfk::W);
    S = std::min(1, int(input.IsKeyPressed(sfk::S)) + S) - input.IsKeyReleased(sfk::S);
    auto rotation = static_cast<float>(D - A);
    auto translation = static_cast<float>(S - W);


    if (translation != 0 || rotation != 0) {
      bool collision_flag = false;



      player_->Move(translation * delta_time);
      player_->Rotate(rotation * delta_time);
      for ( const auto& w: objects_ ) {
        if ( player_->Intersect(*w)) {
          collision_flag = true;
          break;
        }
      }


      if ( collision_flag ) {

        player_->Move(-translation * delta_time);
        player_->Rotate(-rotation * delta_time);

      } else {
        auto pos = player_->GetPosition();
        auto dir = player_->GetDirection();
        std::cout << "Position: (" << pos.x << "; " << pos.y << ") dir: " << dir << std::endl;
        Message<GameEventType> msg;
        msg.header.id = GameEventType::ClientUpdatePosition;
        msg << passport_ << player_->GetPosition() << player_->GetDirection();
        networker->Send(msg);
      }


    }
  }
  if (input.IsLeftButtonPressed() && kill_server_btn_.Contains(input.GetMousePosition())){
    networker->StopServer();
  }
}

void PlayState::Draw(sf::RenderWindow &window) {
  window.clear(sf::Color::Black);
  window.draw(background_);

  if (text_.GetVisible()) text_.Draw(window);
  else {
    player_->Draw(window);

    for ( const auto & w: objects_)
      w->Draw(window);
  }

  kill_server_btn_.Draw(window);
  window.display();
}
void PlayState::OnEntry() {
  server_accepted_connection_.store(false);
  auto &networker = GetContext()->network_manager;
  networker->SearchServers({8888, 8889, 8890}, 3);
  networker->SetOnReceiveHandler([this](std::shared_ptr<Message<GameEventType>> &&message) {
    OnReceiveHandler(std::move(message));
  });
}

void PlayState::OnExit() {
  GameState::OnExit();
}

void PlayState::OnReceiveHandler(std::shared_ptr<Message<GameEventType>> &&message) {
  auto server_msg = *(message);

  switch (server_msg.header.id) {
    case GameEventType::ServerApproveConnection: {
      server_msg >> passport_;
      std::cout << "[CLIENT] Server approved connection. Your ID: " << passport_ << std::endl;
      server_accepted_connection_.store(true);
      break;
    }
    case GameEventType::ServerUpdateNetworkData: {
      sf::Vector2f other_player_position;
      uint32_t other_player_id;
      float direction;
      sf::Vector2f position;
      server_msg >> direction >> position >> other_player_id;
      if (other_player_id == passport_) return;
      /*
      std::cout << "[CLIENT] Received other player location: ("
                << other_player_position.x << ": "
                << other_player_position.y << ")" << std::endl;

      std::cout << "[CLIENT] TOTAL PLAYERS: " << other_players_.size() << "\t[";
      for (auto& [id, _] : other_players_) std::cout << id << ", ";
      std::cout << "]" << std::endl;
      */
      mutex_.lock();
      if (auto other_player_ptr = other_players_.find(other_player_id); other_player_ptr != other_players_.end()){
        other_player_ptr->second->SetDirection(direction);
        other_player_ptr->second->SetPosition(position);
      }else{
        auto& other_player = other_players_[other_player_id];
        auto& resource_manager = ResourceManager::GetInstance();
        auto& player_texture = resource_manager.GetTexture("enemy_tank");
        other_player = std::make_unique<Player>(player_texture, player_size);
        objects_.push_back(std::move(other_player));
      }
      mutex_.unlock();

      break;
    }
    case GameEventType::ServerNotifyShutdown: {
      break;
    }
    default: break;
  }
}


float RandomFloat(float min, float max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(min * 10000, max * 10000);
  return dis(gen) / 10000.0f;
}

sf::Vector2f RandomSize(float minSize, float maxSize) {
  return {RandomFloat(minSize, maxSize)*5.0f, RandomFloat(minSize, maxSize)};
}

sf::Vector2f RandomPosition(float minX, float minY, float maxX, float maxY) {
  return {RandomFloat(minX, maxX), RandomFloat(minY, maxY)};
}



bool CheckIntersection(const Wall &newWall, const std::vector<std::unique_ptr<GameObject>> &existingWalls) {
  for (const auto &wall : existingWalls) {
    if (newWall.GetSprite().getGlobalBounds().findIntersection(wall->GetSprite().getGlobalBounds())) {
      return true;
    }
  }
  return false;
}

void GenerateWalls(sf::Texture &wall_texture, std::vector<std::unique_ptr<GameObject>> &objects, size_t count) {
  const float minSize = 10.f;
  const float maxSize = 50.f;
  const float minX = 0.f;
  const float minY = 0.f;
  const float maxX = 800.f;
  const float maxY = 600.f;

  for (size_t i = 0; i < count; ++i) {
    bool validWall = false;
    Wall newWall(wall_texture, RandomSize(minSize, maxSize));

    while (!validWall) {
      newWall.SetPosition(RandomPosition(minX, minY, maxX, maxY));
      newWall.Animate();

      if (!CheckIntersection(newWall, objects)) {
        validWall = true;
      }
    }

    objects.push_back(std::make_unique<Wall>(std::move(newWall)));
  }
}