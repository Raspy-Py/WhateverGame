#include "whatever_engine.h"
#include "state_manager.h"
#include "game_state.h"
#include "Player.hpp"

WhateverEngine::WhateverEngine(){
  context_ = std::make_shared<Context>();
  context_->window_->create(sf::VideoMode(sf::Vector2u(800, 600)), "WhateverGame", sf::Style::Default);
  context_->state_manager_->PushState(CreateEntryState(context_));
}

WhateverEngine::~WhateverEngine() {

}

int WhateverEngine::Run() {
  sf::Clock clock;
  float delta_time = 0;
  auto player = std::make_shared<Player>();
  
  do {

    // Update the stuff you want to update
    // ...

     delta_time = clock.restart().asMicroseconds();
  } while (DoFrame(delta_time));
  return 0;
}

bool WhateverEngine::DoFrame(float delta_time) {
  // Break the main game loop if there are not any states to update
  if (!context_->state_manager_->StatesAvailable())
    return false;

  context_->state_manager_->DoFrame(delta_time, *(context_->window_));

  return true;
}

void WhateverEngine::DispatchEvents() {


}