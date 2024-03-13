#include "command.h"


void Command::AddAction(Action *action) {
  // Add new action
  actions_.push_back(action);
}

void Command::Execute() {
  // Execute all the actions that this command has to do.
  for ( size_t i = 0; i < actions_.size(); ++i ) {
    actions_[i]->Execute();
  }
}