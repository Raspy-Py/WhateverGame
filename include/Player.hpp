#pragma once
#include <SFML/Graphics.hpp>

class Player{

public:
    Player();
    Player(const std::pair<float, float>& pos, const std::pair<float, float>& size
           ,const char* file);
    ~Player();

    void moveRight();
    void setRectSize();
    void setRectPos();

    sf::RectangleShape* getShape();


private:
    sf::RectangleShape rect;
    sf::Texture texture;
    sf::Vector2f size;
    sf::Vector2f position;

};