#ifndef WHATEVERGAME_SOURCE_ENGINE_COMMAND_H_
#define WHATEVERGAME_SOURCE_ENGINE_COMMAND_H_

#include <vector>
#include <iostream>
#include "actions/action.h"


class Command {
 public:
  virtual ~Command();
  void Execute();
  void AddAction(Action* action);

 private:
  std::vector<Action*> actions_;
};


#endif //WHATEVERGAME_SOURCE_ENGINE_COMMAND_H_
