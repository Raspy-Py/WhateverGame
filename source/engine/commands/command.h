#ifndef WHATEVERGAME_SOURCE_ENGINE_COMMAND_H_
#define WHATEVERGAME_SOURCE_ENGINE_COMMAND_H_

#include <iostream>


class Command {
 public:
  Command() = default;
  virtual ~Command() = default;
  virtual void Execute();

 private:
};


#endif //WHATEVERGAME_SOURCE_ENGINE_COMMAND_H_
