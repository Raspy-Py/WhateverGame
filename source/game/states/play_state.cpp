#include "play_state.h"
#include <iostream>

#include "engine/engine_common.h"

PlayState::PlayState(std::shared_ptr<Context> context)
  : GameState(std::move(context)),
    passport_(0) {
  player_rect_.setSize(player_size);
  player_rect_.setFillColor(sf::Color::Red);
  player_rect_.setOrigin(player_size/2.f);
  player_rect_.setPosition({0.f, 0.f});

  auto& resource_manager = ResourceManager::GetInstance();
  auto& font = resource_manager.GetFont("gothic");
  text_ = std::move(Text(font, "Searching for server...", {400.f, 300.f}));
  text_.SetVisible(true);

  kill_server_btn_ = std::move(Button(font, "Kill Server", {{10.f,540.f}, {300.f,50.f}}));
}

void PlayState::Update(float delta_time) {
  using sfk = sf::Keyboard::Key;
  auto& input = GetInputManager();
  auto &networker = GetContext()->network_manager;
  if (text_.GetVisible()) {
    auto servers = networker->GetAvailableServer();
    if (!servers.empty()){
      text_.SetVisible(false);
      ServerAddress server = servers[0];
      networker->Connect(server.host, server.port);
    }
  }else {
    static int A = 0, D = 0, W = 0, S = 0;
    A = std::min(1, int(input.IsKeyPressed(sfk::A)) + A) - input.IsKeyReleased(sfk::A);
    D = std::min(1, int(input.IsKeyPressed(sfk::D)) + D) - input.IsKeyReleased(sfk::D);
    W = std::min(1, int(input.IsKeyPressed(sfk::W)) + W) - input.IsKeyReleased(sfk::W);
    S = std::min(1, int(input.IsKeyPressed(sfk::S)) + S) - input.IsKeyReleased(sfk::S);

    static sf::Vector2f speed_vector{};
    speed_vector = {
        static_cast<float>(D - A),
        static_cast<float>(S - W)
    };

    if (speed_vector.length() > 0.0f) {
      speed_vector = speed_vector.normalized();
      auto new_position = player_rect_.getPosition() + speed_vector * delta_time * 1000.f;
      player_rect_.setPosition(new_position);
      if (server_accepted_connection_.load() || true) {
        Message<GameEventType> msg;
        msg.header.id = GameEventType::ClientUpdatePosition;
        msg << passport_ << new_position;
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
    window.draw(player_rect_);
    for (auto& [id, player] : other_players_)
      window.draw(player);
  }

  kill_server_btn_.Draw(window);
  window.display();
}
void PlayState::OnEntry() {
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
      std::cout << "[CLIENT] Server approved connection. " << std::endl;
      server_msg >> passport_;
      server_accepted_connection_ = true;
      break;
    }
    case GameEventType::ServerUpdateNetworkData: {
      sf::Vector2f other_player_position;
      uint32_t other_player_id;

      server_msg >> other_player_position >> other_player_id;
      /*
      std::cout << "[CLIENT] Received other player location: ("
                << other_player_position.x << ": "
                << other_player_position.y << ")" << std::endl;
      */
      mutex_.lock();
      if (auto other_player_ptr = other_players_.find(other_player_id); other_player_ptr != other_players_.end()){
        other_player_ptr->second.setPosition(other_player_position);
      }else{
        auto& other_player = other_players_[other_player_id];
        other_player.setSize(player_size);
        other_player.setOrigin(player_size/2.f);
        other_player.setPosition(other_player_position);
        other_player.setFillColor(sf::Color::Cyan);
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
