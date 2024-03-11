#include "game_state.h"
#include "state_manager.h"

void GameState::PopThisState(){
  state_manager_->IssuePop();
}

void GameState::PushNewState(std::unique_ptr<GameState> game_state){
  state_manager_->IssuePush(std::move(game_state));
}