#include "engine/engine_common.h"

#include <memory>
#include <iostream>

class MainMenuState : public GameState{
 public:
  explicit MainMenuState(std::shared_ptr<StateManager> state_manager) : GameState(std::move(state_manager)){}

  void Update(float delta_time) override{
    std::cout << "Updating entry state." << std::endl;

    PopThisState();
  }

  void Draw(sf::RenderWindow& window) override{
    std::cout << "Drawing entry state." << std::endl;
  }

  void OnEntry() override{
    std::cout << "Entering entry state." << std::endl;
  }

  void OnExit() override{
    std::cout << "Exiting entry state." << std::endl;
  }
};

std::unique_ptr<GameState> CreateEntryState(std::shared_ptr<StateManager> state_manager){
  // Some resource loading
  // ...

  return std::make_unique<MainMenuState>(state_manager);
}

