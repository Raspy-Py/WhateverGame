#include "play_state.h"
#include <iostream>


PlayState::PlayState(std::shared_ptr<Context> context) :
  GameState(std::move(context)), player_position_(400, 300), player_size_(50, 50),
  player_position2_(200, 150), player_size2_(50, 50){
  player_rect_.setSize(player_size_);
  player_rect_.setFillColor(sf::Color::Red);
  player_rect_.setPosition(player_position_);

  player_rect2_.setSize(player_size2_);
  player_rect2_.setFillColor(sf::Color::Blue);
  player_rect2_.setPosition(player_position2_);
}


void PlayState::Update(float delta_time) {
  GetContext()->input_manager_->HandleInput(*GetContext()->window_);
  auto next_input = GetContext()->input_manager_->PopNextInput();
  bool is_client = GetContext()->network_manager_->IsClient();
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
  if ( is_client ) {
    std::cout << "sending data: " << player_position_.x << " " << player_position_.y
    << std::endl;

    GetContext()->network_manager_->
          SendData(GameEventType::MovePlayer, player_position_.x, player_position_.y);
    player_rect_.setPosition(player_position_);
    // TODO: get packet from server to update other's player position

  }
  else {
    player_rect_.setPosition(player_position_);
    auto packet = GetContext()->network_manager_->ReceiveData();
    if ( !packet ) {
      return;
    }
    auto msg = *packet->message;
    float x, y;
    msg >> y >> x;
    std::cout << x << " " << y << std::endl;
    player_position2_.x = x;
    player_position2_.y = y;
    player_rect2_.setPosition(player_position2_);
  }
}

void PlayState::Draw(sf::RenderWindow &window) {
  bool is_client = GetContext()->network_manager_->IsClient();

  GetContext()->window_->clear(sf::Color::Black);

  GetContext()->window_->draw(player_rect_);
  if ( !is_client ) {
    GetContext()->window_->draw(player_rect2_);
  }

  GetContext()->window_->display();
}