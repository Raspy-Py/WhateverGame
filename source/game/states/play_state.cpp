#include "play_state.h"
#include <iostream>

#include "engine/engine_common.h"

PlayState::PlayState(std::shared_ptr<Context> context)
  : GameState(std::move(context)),
    passport_(0) {

  auto& resource_manager = ResourceManager::GetInstance();
  auto& font = resource_manager.GetFont("gothic");
  auto& player_texture = resource_manager.GetTexture("tank");

  player_ = std::make_unique<Player>(player_texture, player_size);
  text_ = std::move(Text(font, "Searching for server...", {400.f, 300.f}));
  text_.SetVisible(true);


  // fake player to test collision
  auto& other_player = other_players_[5];
  other_player = std::make_unique<Player>(player_texture, player_size);
  other_player->SetPosition({400, 400});

  kill_server_btn_ = std::move(Button(font, "Kill Server", {{10.f,540.f}, {300.f,50.f}}));
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

    float rotation = static_cast<float>(D - A);
    float translation = static_cast<float>(S - W);

    if (translation != 0 || rotation != 0) {
      player_->Rotate(rotation * delta_time);

      bool move_flag = true;

      for ( const auto& [_, other_pl] : other_players_ ) {
        if ( player_->Intersect(*other_pl, translation * delta_time) ) {
          move_flag = false;
          break;
        }
      }

      if ( move_flag ) {
        player_->Move(translation * delta_time);
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

  if (text_.GetVisible()) text_.Draw(window);
  else {
    player_->Draw(window);
    for (auto& [id, player] : other_players_)
      player->Draw(window);
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
