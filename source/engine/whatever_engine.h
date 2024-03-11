#ifndef WHATEVERGAME_SOURCE_WHATEVER_ENGINE_H_
#define WHATEVERGAME_SOURCE_WHATEVER_ENGINE_H_

#include <memory>
#include <SFML/Graphics.hpp>
#include "state_manager.h"
#include "game_state.h"

class WhateverEngine {
 public:
  WhateverEngine();
  ~WhateverEngine();

  int Run();

 private:
  // Translates raw low-level input into high level
  // representation with meta information
  void DispatchEvents();

  // Updates and draws the current game state
  bool DoFrame(float delta_time);

 private:
  // Using a shared pointer, as the GameStates themselves should be able
  // to reference and change the StateManager. This way the client code
  // will gain a full control of state switching
  std::shared_ptr<StateManager> state_manager_;
  sf::RenderWindow window_;
};

// Defined in the client code.
// This function should be used for creating an initial state,
// which will most probably be the main menu, and doing static
// resources loading
std::unique_ptr<GameState> CreateEntryState(std::shared_ptr<StateManager> state_manager);

#endif //WHATEVERGAME_SOURCE_WHATEVER_ENGINE_H_