#include "whatever_engine.h"
#include "state_manager.h"
#include "game_state.h"

WhateverEngine::WhateverEngine(){
  context_ = std::make_shared<Context>();
  context_->window->create(sf::VideoMode(sf::Vector2u(800, 600)), "WhateverGame", sf::Style::Titlebar | sf::Style::Close);
  context_->state_manager->PushState(CreateEntryState(context_));
}

WhateverEngine::~WhateverEngine() {

}

int WhateverEngine::Run() {
  sf::Clock clock;
  float delta_time = 0;

  do {
    DispatchEvents();

    // Update the stuff you want to update
    // ...

    delta_time = clock.restart().asSeconds();
  } while (DoFrame(delta_time));
  return 0;
}

bool WhateverEngine::DoFrame(float delta_time) {
  // Break the main game loop if there are not any states to update
  if (!context_->state_manager->StatesAvailable())
    return false;

  if (context_->window->isOpen()) {
    context_->state_manager->DoFrame(delta_time, *(context_->window));
  }else{
    // The window was closed, so perform the graceful shutdown
    while (context_->state_manager->StatesAvailable())
      context_->state_manager->PopState();

    return false;
  }

  return true;
}

void WhateverEngine::DispatchEvents() {
  context_->input_manager->HandleInput(*(context_->window));
}