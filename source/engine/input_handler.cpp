#include "input_handler.h"


void InputHandler::handleInput(sf::Keyboard::Key * key)
{
  if (*key == sf::Keyboard::Key::X)
    buttonX_->execute();
  else if (*key == sf::Keyboard::Key::Y)
    buttonY_->execute();
  else if (*key == sf::Keyboard::Key::A)
    buttonA_->execute();
  else if (*key == sf::Keyboard::Key::B)
    buttonB_->execute();
}
