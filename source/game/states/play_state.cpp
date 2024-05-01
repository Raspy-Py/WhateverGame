#include "play_state.h"
#include <iostream>

#include "engine/engine_common.h"

PlayState::PlayState(std::shared_ptr<Context> context)
  : GameState(std::move(context)),
    player_position_(400, 300),
    player_size_(50, 50) {
  player_rect_.setSize(player_size_);
  player_rect_.setFillColor(sf::Color::Red);
  player_rect_.setPosition(player_position_);

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

    if (speed_vector.length() > 0.0f) speed_vector = speed_vector.normalized();

    player_position_ += speed_vector * delta_time * 1000.f;
    player_rect_.setPosition(player_position_);
  }
  if (input.IsLeftButtonPressed() && kill_server_btn_.Contains(input.GetMousePosition())){
    networker->StopServer();
  }
}

void PlayState::Draw(sf::RenderWindow &window) {
  GetWindow().clear(sf::Color::Black);

  if (text_.GetVisible()) text_.Draw(window);
  else GetWindow().draw(player_rect_);

  kill_server_btn_.Draw(window);
  GetWindow().display();
}
void PlayState::OnEntry() {
  auto& networker = GetContext()->network_manager;
  networker->SearchServers({BROADCASTING_PORT}, 3);
}
void PlayState::OnExit() {
  GameState::OnExit();
}
