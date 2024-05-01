#include "input_manager.h"
#include <cstring>
#include <iostream>

void InputManager::HandleInput(sf::RenderWindow& window_){
  keys_pressed_.fill(false);
  keys_released_.fill(false);
  left_button_released_ = left_button_pressed_ = false;
  right_button_released_ = right_button_pressed_ = false;

  sf::Event event;

  while(window_.pollEvent(event)){
    switch (event.type){
      case sf::Event::KeyPressed:
        keys_pressed_[static_cast<unsigned>(event.key.code)] = true;
        break;
      case sf::Event::KeyReleased:
        keys_released_[static_cast<unsigned>(event.key.code)] = true; break;
      case sf::Event::MouseButtonPressed:{
        if (event.mouseButton.button == sf::Mouse::Button::Left) left_button_pressed_ = true;
        if (event.mouseButton.button == sf::Mouse::Button::Right) right_button_pressed_ = true;
        break;
      }
      case sf::Event::MouseButtonReleased:{
        if (event.mouseButton.button == sf::Mouse::Button::Left) left_button_released_ = true;
        if (event.mouseButton.button == sf::Mouse::Button::Right) right_button_released_ = true;
        break;
      }
      case sf::Event::Closed:
        window_.close();
        break;
    };
  }

  mouse_position_ = sf::Mouse::getPosition(window_);
}
