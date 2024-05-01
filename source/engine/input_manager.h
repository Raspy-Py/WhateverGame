#ifndef WHATEVERGAME_SOURCE_ENGINE_INPUT_MANAGER_H_
#define WHATEVERGAME_SOURCE_ENGINE_INPUT_MANAGER_H_

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <queue>
#include <unordered_map>


class InputManager
{
 public:
  InputManager() = default;
  ~InputManager() = default;

  void HandleInput(sf::RenderWindow& window_);

  [[nodiscard]] bool IsKeyPressed(sf::Keyboard::Key key) const { return keys_pressed_[static_cast<unsigned>(key)]; }
  [[nodiscard]] bool IsKeyReleased(sf::Keyboard::Key key) const { return keys_released_[static_cast<unsigned>(key)]; }
  [[nodiscard]] bool IsLeftButtonPressed() const { return left_button_pressed_; }
  [[nodiscard]] bool IsLeftButtonReleased() const { return left_button_released_; }
  [[nodiscard]] bool IsRightButtonPressed() const { return right_button_pressed_; }
  [[nodiscard]] bool IsRightButtonReleased() const { return right_button_released_; }
  [[nodiscard]] sf::Vector2i GetMousePosition() const { return mouse_position_; }

 private:
  std::array<bool, sf::Keyboard::KeyCount> keys_pressed_{};
  std::array<bool, sf::Keyboard::KeyCount> keys_released_{};
  bool left_button_pressed_ = false;
  bool left_button_released_ = false;
  bool right_button_pressed_ = false;
  bool right_button_released_ = false;

  sf::Vector2i mouse_position_;
};



#endif //WHATEVERGAME_SOURCE_ENGINE_INPUT_MANAGER_H_
