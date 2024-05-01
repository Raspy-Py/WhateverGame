#include "play_state.h"
#include <iostream>


 PlayState::PlayState(std::shared_ptr<Context> context) :
  GameState(std::move(context)), player_position_(400, 300), player_size_(50, 50) {
  player_rect_.setSize(player_size_);
  player_rect_.setFillColor(sf::Color::Red);
  player_rect_.setPosition(player_position_);
}

void PlayState::Update(float delta_time) {
  GetContext()->input_manager->HandleInput(GetWindow());
  auto next_input = GetInputManager().PopNextInput();
  switch (next_input) {
    case sf::Keyboard::Key::Left:
      player_position_.x -= 0.1f * delta_time;
      break;
    case sf::Keyboard::Key::Right:
      player_position_.x += 0.1f * delta_time;
      break;
    case sf::Keyboard::Key::Up:
      player_position_.y -= 0.1f * delta_time;
      break;
    case sf::Keyboard::Key::Down:
      player_position_.y += 0.1f * delta_time;
      break;
    default:
      break;
  }

  player_rect_.setPosition(player_position_);
}

void PlayState::Draw(sf::RenderWindow &window) {
  GetWindow().clear(sf::Color::Black);
  GetWindow().draw(player_rect_);
  GetWindow().display();
}