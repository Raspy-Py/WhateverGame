#ifndef WHATEVERGAME_SOURCE_ENGINE_INPUT_MANAGER_H_
#define WHATEVERGAME_SOURCE_ENGINE_INPUT_MANAGER_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <queue>
#include <unordered_map>


class InputManager
{
 public:
  InputManager() = default;
  ~InputManager() = default;

  void HandleInput(sf::RenderWindow& window_);
  void InputToQueue(const sf::Keyboard::Key& key);
  sf::Keyboard::Key PopNextInput();

//  void ExecuteCommand();
//  void AddCommand(const sf::Keyboard::Key& key,
//                  const std::shared_ptr<Command>& command,
//                  size_t state);
//  void RemoveCommand(const sf::Keyboard::Key& key, int state);

  void SetActiveState(size_t state);
  int GetActiveState() const;

 private:
  size_t active_state_ = 0;
  std::queue<sf::Keyboard::Key> inputs_queue_;
//  std::unordered_map<size_t, std::unordered_map< sf::Keyboard::Key,
//              std::vector< std::shared_ptr<Command> >>> commands_map_;
};



#endif //WHATEVERGAME_SOURCE_ENGINE_INPUT_MANAGER_H_
