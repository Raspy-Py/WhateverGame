#ifndef WHATEVERGAME_SOURCE_ENGINE_GAME_STATE_H_
#define WHATEVERGAME_SOURCE_ENGINE_GAME_STATE_H_

#include "SFML/Graphics.hpp"
#include <memory>
#include "state_manager.h"
#include "resource_manager.h"
#include "input_manager.h"
#include "network_manager.h"

class Context {
 public:
  std::unique_ptr<StateManager> state_manager;
  std::unique_ptr<sf::RenderWindow> window;
  std::unique_ptr<InputManager> input_manager;
  std::unique_ptr<NetworkManager> network_manager;

  Context() {
    state_manager = std::make_unique<StateManager>();
    input_manager = std::make_unique<InputManager>();
    window = std::make_unique<sf::RenderWindow>();
    // TODO: the whole "Context" thing is bullshit. Especially those resources
    //  with non-default constructors. Redesign this part later.
    network_manager = std::make_unique<NetworkManager>("./WhateverServer");
  }
};

class GameState {
 public:
  explicit GameState(std::shared_ptr<Context> context) : context_(std::move(context)) {}
  virtual ~GameState() = default;

  virtual void OnEntry() {}
  virtual void OnExit() {}
  virtual void Update(float delta_time) {}
  virtual void Draw(sf::RenderWindow &window) {}

 protected:
  // Some shortcuts
  sf::RenderWindow &GetWindow() { return *(GetContext()->window); }
  StateManager &GetStateManager() { return *(GetContext()->state_manager); }
  InputManager &GetInputManager() { return *(GetContext()->input_manager); }

 protected:
  void PopThisState() { GetStateManager().IssuePop(); }
  void PushNewState(std::unique_ptr<GameState> game_state) { GetStateManager().IssuePush(std::move(game_state)); }

  [[nodiscard]] std::shared_ptr<Context> GetContext() const { return context_; }

 private:
  std::shared_ptr<Context> context_;
};

#endif // WHATEVERGAME_SOURCE_ENGINE_GAME_STATE_H_
