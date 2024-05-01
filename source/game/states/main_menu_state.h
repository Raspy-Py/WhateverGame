#ifndef WHATEVERGAME_SOURCE_GAME_STATES_MAIN_MENU_STATE_H_
#define WHATEVERGAME_SOURCE_GAME_STATES_MAIN_MENU_STATE_H_

#include "engine/engine_common.h"
#include "game/states/play_state.h"
#include "engine/resource_manager.h"

class MainMenuState : public GameState{
 public:
  explicit MainMenuState(std::shared_ptr<Context> context) :
      GameState(std::move(context)), main_menu_(font_, font_, font_) {
    font_ = ResourceManager::GetFont("../assets/fonts/IdealGothic Bold.otf");
  }

  void Update(float delta_time) override{
    GetInputManager().HandleInput(GetWindow());
    auto next_input = GetInputManager().PopNextInput();

    switch (next_input) {
      case sf::Keyboard::Key::Up:
        if (selected_ > 0) {
          --selected_;
        }
        break;
      case sf::Keyboard::Key::Down:

        if (selected_ < 2) {
          ++selected_;
        }
        break;
      case sf::Keyboard::Key::Enter:{
        PopThisState();
        PushNewState(std::make_unique<PlayState>(GetContext()));
      }
      default:
        break;
    }

  }

  void Draw(sf::RenderWindow& window) override{
    GetWindow().clear(sf::Color::Black);

    for ( size_t i = 0; i < 3; ++i ) {
      main_menu_[i].setFont(font_);
      main_menu_[i].setFillColor(sf::Color{ sf::Color::White});
      main_menu_[i].setString(buttons[i]);
      main_menu_[i].setCharacterSize(30);
      main_menu_[i].setPosition(sf::Vector2f( 800.0f/3, 600.0f/4 + (150.0f*static_cast<float>(i)) ));
      GetWindow().draw(main_menu_[i]);
    }
    main_menu_[selected_].setFillColor(sf::Color{ 255, 204, 140});
    GetWindow().draw(main_menu_[selected_]);
    GetWindow().display();
  }

  void OnEntry() override{
    std::cout << "Entering entry state." << std::endl;
  }

  void OnExit() override{
    GetWindow().clear(sf::Color::Black);
    GetWindow().display();
    std::cout << "Exiting entry state." << std::endl;
  }

 private:
  sf::Font font_;
  sf::Text main_menu_[3];
  std::string buttons[3] = {"Host the game", "Join the game", "         Exit"};
  size_t selected_ = 0;
};

#endif //WHATEVERGAME_SOURCE_GAME_STATES_MAIN_MENU_STATE_H_
