#ifndef WHATEVERGAME_SOURCE_ENGINE_INPUT_HANDLER_H_
#define WHATEVERGAME_SOURCE_ENGINE_INPUT_HANDLER_H_

#include <SFML/Window.hpp>
#include "command.h"

class InputHandler
{
 public:
  void handleInput(sf::Keyboard::Key * key);


 private:
  Command* buttonX_;
  Command* buttonY_;
  Command* buttonA_;
  Command* buttonB_;
};



#endif //WHATEVERGAME_SOURCE_ENGINE_INPUT_HANDLER_H_
