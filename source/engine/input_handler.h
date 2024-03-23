#ifndef WHATEVERGAME_SOURCE_ENGINE_INPUT_HANDLER_H_
#define WHATEVERGAME_SOURCE_ENGINE_INPUT_HANDLER_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <queue>
#include <unordered_map>

#include "commands/command.h"

class InputHandler
{
 public:
  InputHandler() = default;
  ~InputHandler() = default;
  void HandleInput(sf::RenderWindow& window_);
  void InputToQueue(const sf::Keyboard::Key& key);
  void ExecuteCommand();
  void AddCommand(const sf::Keyboard::Key& key,
                  const std::shared_ptr<Command>& command);

 private:
  std::queue< sf::Keyboard::Key > inputs_queue_;
  std::unordered_map<sf::Keyboard::Key, std::vector<std::shared_ptr<Command>> > commands_map_;
};



#endif //WHATEVERGAME_SOURCE_ENGINE_INPUT_HANDLER_H_
