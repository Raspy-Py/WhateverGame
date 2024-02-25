#include "Menu.hpp"
#include <iostream>


Menu::Menu(float w, float h, sf::Font& font): main_menu{sf::Text(font), sf::Text(font), sf::Text(font)} {
  if ( !font.loadFromFile("../assets/fonts/IdealGothic Bold.otf") ) {
    std::cerr << "Error while loading font\n";
  }
  std::string buttons[3] = {"Host the game", "Join the game", "         Exit"};

  for (size_t i = 0; i < 3; ++i) {
    main_menu[i].setFont(font);
    main_menu[i].setFillColor(sf::Color{ sf::Color::White});
    main_menu[i].setString(buttons[i]);
    main_menu[i].setCharacterSize(150);
    main_menu[i].setPosition(sf::Vector2f( w/3, h/4 + (200*i) ));
  }

  selected = 0;
}

Menu::~Menu() {}

void Menu::setSeleced(int n) {
  selected = n;
}

int Menu::pressed() {
  return selected;
}

void Menu::draw(sf::RenderWindow &window) {
  for (size_t i = 0; i < 3; ++i) {
    window.draw(main_menu[i]);
  }
}

void Menu::MoveDown() {
  if (selected + 1 <= 3) {
    main_menu[selected++].setFillColor(sf::Color::White);
    if (selected == 3) {
      selected = 0;
    }
    main_menu[selected].setFillColor(sf::Color{ 255, 204, 140});
  }
}

void Menu::MoveUp() {
  if (selected - 1 >= -1) {
    main_menu[selected--].setFillColor(sf::Color::White);
    if (selected == -1) {
      selected = 2;
    }
    main_menu[selected].setFillColor(sf::Color{ 255, 204, 140});
  }
}