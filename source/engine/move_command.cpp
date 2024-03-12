#include "command.h"


class MoveCommand : public Command
{
 public:
  virtual void execute() {
    std::cout << "Moving..." << std::endl;
  }
};