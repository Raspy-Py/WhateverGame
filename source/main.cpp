#include "engine/engine_common.h"
#include "states/play_state.h"
#include "engine/resource_manager.h"

#include <memory>
#include <iostream>



class MainMenuState : public GameState{
 public:
  explicit MainMenuState(std::shared_ptr<Context> context) :
  GameState(std::move(context)), main_menu_(font_, font_, font_){
    // TODO: get font from ResourceManager
//    if (!font_.loadFromFile("../assets/fonts/IdealGothic Bold.otf"))
//      std::cerr << "Error while loading font\n";
    // should output not found in cache
    font_ = GetContext()->resource_manager_->GetFont("../assets/fonts/IdealGothic Bold.otf");
    // should output found in cache
    font_ = GetContext()->resource_manager_->GetFont("../assets/fonts/IdealGothic Bold.otf");
  }

  void Update(float delta_time) override{

    GetContext()->input_manager_->HandleInput(*GetContext()->window_);
    auto next_input = GetContext()->input_manager_->PopNextInput();

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
      case sf::Keyboard::Key::Enter:

        PopThisState();
        PushNewState(std::make_unique<PlayState>(GetContext()));
      default:
        break;
    }

  }

  void Draw(sf::RenderWindow& window) override{
    GetContext()->window_->clear(sf::Color::Black);

    for ( size_t i = 0; i < 3; ++i ) {
      main_menu_[i].setFont(font_);
      main_menu_[i].setFillColor(sf::Color{ sf::Color::White});
      main_menu_[i].setString(buttons[i]);
      main_menu_[i].setCharacterSize(30);
      main_menu_[i].setPosition(sf::Vector2f( 800.0f/3, 600.0f/4 + (150.0f*static_cast<float>(i)) ));
      GetContext()->window_->draw(main_menu_[i]);
    }
    main_menu_[selected_].setFillColor(sf::Color{ 255, 204, 140});
    GetContext()->window_->draw(main_menu_[selected_]);


    GetContext()->window_->display();

  }

  void OnEntry() override{
    std::cout << "Entering entry state." << std::endl;
  }

  void OnExit() override{
    GetContext()->window_->clear(sf::Color::Black);
    GetContext()->window_->display();
    std::cout << "Exiting entry state." << std::endl;
  }

 private:
  sf::Font font_;
  sf::Text main_menu_[3];
  std::string buttons[3] = {"Host the game", "Join the game", "         Exit"};
  size_t selected_ = 0;


};

std::unique_ptr<GameState> CreateEntryState(std::shared_ptr<Context> context){
  // Some resource loading
  // ...

  return std::make_unique<MainMenuState>(context);
}

