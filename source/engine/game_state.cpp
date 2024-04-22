#include "game_state.h"
#include "state_manager.h"

void GameState::PopThisState(){
  context_->state_manager_->IssuePop();
}

void GameState::PushNewState(std::unique_ptr<GameState> game_state){
  context_->state_manager_->IssuePush(std::move(game_state));
}