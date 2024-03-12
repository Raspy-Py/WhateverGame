#ifndef WHATEVERGAME_SOURCE_ENGINE_COMMAND_H_
#define WHATEVERGAME_SOURCE_ENGINE_COMMAND_H_

#include "iostream"


class Command {
 public:
  virtual ~Command();
  virtual void execute();
};


#endif //WHATEVERGAME_SOURCE_ENGINE_COMMAND_H_
