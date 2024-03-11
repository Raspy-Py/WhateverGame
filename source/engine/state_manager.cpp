#include "state_manager.h"
#include "game_state.h"

bool StateManager::StatesAvailable(){
  return !game_states_.empty();
}

void StateManager::PushState(std::unique_ptr<GameState> game_state){
  game_state->OnEntry();
  game_states_.emplace(std::move(game_state));
}

void StateManager::PopState(){
  game_states_.top()->OnExit();
  game_states_.pop();
}

void StateManager::DoFrame(float delta_time, sf::RenderWindow& window){
  game_states_.top()->Update(delta_time);
  game_states_.top()->Draw(window);

  if (should_pop_){
    PopState();
    should_pop_ = false;
  }

  if (pending_state_){
    PushState(std::move(pending_state_));
  }
}

void StateManager::IssuePop() {
  should_pop_ = true;
}

void StateManager::IssuePush(std::unique_ptr<GameState> game_state) {
  pending_state_ = std::move(game_state);
}