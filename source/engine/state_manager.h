#ifndef WHATEVERGAME_SOURCE_ENGINE_STATE_MANAGER_H_
#define WHATEVERGAME_SOURCE_ENGINE_STATE_MANAGER_H_

#include <vector>
#include <stack>
#include <memory>
#include "SFML/Graphics.hpp"

class GameState;

class StateManager {
 public:
  StateManager() = default;
  ~StateManager() = default;

  bool StatesAvailable();

  void PushState(std::unique_ptr<GameState> game_state);
  void PopState();

  // Used to pop/push state after current state finished
  // updating and drawing
  void IssuePush(std::unique_ptr<GameState> game_state);
  void IssuePop();

  void DoFrame(float delta_time, sf::RenderWindow& window);

 private:
  bool should_pop_ = false;
  std::unique_ptr<GameState> pending_state_;
  std::stack<std::unique_ptr<GameState>> game_states_;
};

#endif //WHATEVERGAME_SOURCE_ENGINE_STATE_MANAGER_H_