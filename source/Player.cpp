#include "Player.hpp"
#include <iostream>


Player::Player() {

}

Player::Player(const std::pair<float, float>& pos, const std::pair<float, float>& sz
        ,const char* file) : size(sz.first, sz.second),
        position(pos.first, pos.second) {
    // loading texture
    bool isLoaded = texture.loadFromFile(file);
    rect.setTexture(&texture);


    setRectSize();
    setRectPos();
}


Player::~Player() {

}

void Player::setRectSize() {
    rect.setSize(size);
}

void Player::setRectPos() {

    rect.setPosition(position);
}

sf::RectangleShape* Player::getShape() {
    return &rect;
}



void Player::moveRight() {
    position.x += 1;
    rect.setPosition({position.x + 1, position.y });
}