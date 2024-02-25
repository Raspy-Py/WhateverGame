#pragma once
#include <SFML/Graphics.hpp>


class Menu {
 public:

  sf::Text main_menu[3];

  Menu(float w, float h, sf::Font& font);

  void draw(sf::RenderWindow& window);
  void MoveUp();
  void MoveDown();
  void setSeleced(int n);
  int pressed();

  ~Menu();

 private:
  int selected;
};