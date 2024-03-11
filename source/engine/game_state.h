#ifndef WHATEVERGAME_SOURCE_ENGINE_GAME_STATE_H_
#define WHATEVERGAME_SOURCE_ENGINE_GAME_STATE_H_

#include <SFML/Graphics.hpp>
#include <utility>

class StateManager;

class GameState {
 public:
  explicit GameState(std::shared_ptr<StateManager> state_manager) : state_manager_(std::move(state_manager)) {}
  virtual ~GameState() = default;

  virtual void OnEntry() {}
  virtual void OnExit() {}
  virtual void Update(float delta_time) {}
  virtual void Draw(sf::RenderWindow& window) {}

 protected:
  void PopThisState();
  void PushNewState(std::unique_ptr<GameState> game_state);

  std::shared_ptr<StateManager> state_manager_;
};

#endif //WHATEVERGAME_SOURCE_ENGINE_GAME_STATE_H_