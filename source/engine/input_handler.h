#ifndef WHATEVERGAME_SOURCE_ENGINE_INPUT_HANDLER_H_
#define WHATEVERGAME_SOURCE_ENGINE_INPUT_HANDLER_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <queue>

#include "commands/command.h"

class InputHandler
{
 public:
  void HandleInput(sf::RenderWindow& window_);
  void InputToQueue(sf::Keyboard::Key * key);
  void ExecuteCommand();

 private:
  std::queue<Command*> commands_queue_;
  Command* buttonX_;
  Command* buttonY_;
  Command* buttonA_;
  Command* buttonB_;
};



#endif //WHATEVERGAME_SOURCE_ENGINE_INPUT_HANDLER_H_
