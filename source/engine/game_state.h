#ifndef WHATEVERGAME_SOURCE_ENGINE_GAME_STATE_H_
#define WHATEVERGAME_SOURCE_ENGINE_GAME_STATE_H_

#include <SFML/Graphics.hpp>
#include <memory>
#include "state_manager.h"
#include "resource_manager.h"
#include "input_manager.h"

//class ResourceManager;
//class StateManager;

class Context {
 public:

  std::unique_ptr<StateManager> state_manager_;
  std::unique_ptr<ResourceManager> resource_manager_;
  std::unique_ptr<sf::RenderWindow> window_;
  std::unique_ptr<InputManager> input_manager_;


  Context(){
    state_manager_ = std::make_unique<StateManager>();
    resource_manager_ = std::make_unique<ResourceManager>();
    input_manager_ = std::make_unique<InputManager>();
    window_ = std::make_unique<sf::RenderWindow>();
  }

  void hello() {
  }
};

class GameState {
 public:
  explicit GameState(std::shared_ptr<Context> context) : context_(std::move(context)) {}
  virtual ~GameState() = default;

  virtual void OnEntry() {}
  virtual void OnExit() {}
  virtual void Update(float delta_time) {}
  virtual void Draw(sf::RenderWindow& window) {}

 protected:
  void PopThisState();
  void PushNewState(std::unique_ptr<GameState> game_state);

  std::shared_ptr<Context> GetContext() const { return context_; }

 private:
  std::shared_ptr<Context> context_;
};

#endif // WHATEVERGAME_SOURCE_ENGINE_GAME_STATE_H_
