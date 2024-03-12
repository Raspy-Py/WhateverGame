#include "command.h"


class FireCommand : public Command
{
 public:
  virtual void execute() {
    std::cout << "Firing..." << std::endl;
  }
};