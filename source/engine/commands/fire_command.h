
#ifndef WHATEVERGAME_SOURCE_ENGINE_COMMANDS_FIRE_COMMAND_H_
#define WHATEVERGAME_SOURCE_ENGINE_COMMANDS_FIRE_COMMAND_H_

#include "command.h"


class FireCommand : public Command {
 public:
  FireCommand() = default;
  ~FireCommand() override = default;
  void Execute() override;

 private:
};

#endif //WHATEVERGAME_SOURCE_ENGINE_COMMANDS_FIRE_COMMAND_H_
