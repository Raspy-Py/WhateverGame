#include "engine/engine_common.h"
#include "engine/resource_manager.h"
#include "states/main_menu_state.h"

#include "yaml-cpp/yaml.h"

// Treat this function as an entry point
std::unique_ptr<GameState> CreateEntryState(std::shared_ptr<Context> context){
  // Some resource loading
  // ...

  ResourceManager::GetInstance().LoadResourceMap("../assets/resources.yaml");

  return std::make_unique<MainMenuState>(context);
}
