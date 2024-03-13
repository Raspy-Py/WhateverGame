#include "whatever_engine.h"
#include "state_manager.h"
#include "game_state.h"

WhateverEngine::WhateverEngine(){
  state_manager_ = std::make_shared<StateManager>();
  state_manager_->PushState(CreateEntryState(state_manager_));
}
WhateverEngine::~WhateverEngine() {

}

int WhateverEngine::Run() {
  float delta_time = 0;
  do {
    DispatchEvents();

    // Update the stuff you want to update
    // ...

    // delta_time = clock::get_time();
  } while (DoFrame(delta_time));
  return 0;
}

bool WhateverEngine::DoFrame(float delta_time) {
  // Break the main game loop if there are not any states to update
  if (!state_manager_->StatesAvailable())
    return false;

  state_manager_->DoFrame(delta_time, window_);

  return true;
}

void WhateverEngine::DispatchEvents() {
  // Handle user inputs
  input_handler_->HandleInput(window_);

}