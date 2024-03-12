#include "command.h"


class JumpCommand : public Command
{
 public:
  virtual void execute() {
    std::cout << "Jumping..." << std::endl;
  }
};