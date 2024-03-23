#ifndef WHATEVERGAME_SOURCE_ENGINE_INPUT_MANAGER_H_
#define WHATEVERGAME_SOURCE_ENGINE_INPUT_MANAGER_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <queue>
#include <unordered_map>

#include "commands/command.h"

class InputManager
{
 public:
  InputManager() = default;
  ~InputManager() = default;

  void HandleInput(sf::RenderWindow& window_);
  void InputToQueue(const sf::Keyboard::Key& key);

  void ExecuteCommand();
  void AddCommand(const sf::Keyboard::Key& key,
                  const std::shared_ptr<Command>& command,
                  int state);
  void RemoveCommand(const sf::Keyboard::Key& key, int state);

  void SetActiveState(int state);
  int GetActiveState() const;

 private:
  int active_state_ = 0;
  std::queue< sf::Keyboard::Key > inputs_queue_;
  std::unordered_map< sf::Keyboard::Key,
              std::vector<std::pair< std::shared_ptr<Command>, int >>> commands_map_;
};



#endif //WHATEVERGAME_SOURCE_ENGINE_INPUT_MANAGER_H_
