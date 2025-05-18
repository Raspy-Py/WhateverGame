#ifndef WHATEVERGAME_SOURCE_GAME_STATES_MAIN_MENU_STATE_H_
#define WHATEVERGAME_SOURCE_GAME_STATES_MAIN_MENU_STATE_H_

#include "engine/engine_common.h"
#include "game/states/play_state.h"
#include "engine/resource_manager.h"

#include "temp_gui.h"

class MainMenuState final : public GameState{
 public:
  explicit MainMenuState(std::shared_ptr<Context> context)
    : GameState(std::move(context)){
    auto& resource_manager = ResourceManager::GetInstance();
    auto& font = resource_manager.GetFont("poppins");

    buttons_["create_game"] = {font, "Create Game", {{250.f,100.f}, {300.f,50.f}}, 40};
    buttons_["join_game"] = {font, "Join Game", {{250.f,160.f}, {300.f,50.f}}, 40};
    buttons_["exit_game"] = {font, "Exit Game", {{250.f,220.f}, {300.f,50.f}}, 40};
  }

  void Update(float delta_time) final{
    auto& input = GetInputManager();
    if (input.IsLeftButtonPressed()){
      auto mouse_position = input.GetMousePosition();
      if (buttons_["create_game"].Contains(mouse_position)){
        auto& networker = GetContext()->network_manager;
        networker->StartServer(SERVER_PORT);
        PushNewState(std::make_unique<PlayState>(GetContext()));
      }else if (buttons_["join_game"].Contains(mouse_position)){
        PushNewState(std::make_unique<PlayState>(GetContext()));
      }else if (buttons_["exit_game"].Contains(mouse_position)){
        PopThisState();
      }
    }
  }

  void Draw(sf::RenderWindow& window) final{
    GetWindow().clear(sf::Color::Black);
    for (auto& [name, button] : buttons_)
      button.Draw(window);
    GetWindow().display();
  }

  void OnEntry() final{
  }

  void OnExit() final{
    GetWindow().clear(sf::Color::Black);
    GetWindow().display();
  }

  std::unordered_map<std::string, Button> buttons_;
};

#endif //WHATEVERGAME_SOURCE_GAME_STATES_MAIN_MENU_STATE_H_
