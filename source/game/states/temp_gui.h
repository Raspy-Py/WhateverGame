#ifndef WHATEVERGAME_SOURCE_GAME_STATES_TEMP_GUI_H_
#define WHATEVERGAME_SOURCE_GAME_STATES_TEMP_GUI_H_

#include "SFML/Graphics.hpp"

class Widget{
 public:
  void SetVisible(bool visible) { visible_ = visible; }
  [[nodiscard]] bool GetVisible() const {return visible_; }

 protected:
  bool visible_;
};

class Button : public Widget{
 public:
  Button() = default;
  Button(sf::Font& font, const std::string& text, sf::Rect<float> rect, unsigned font_size = 50)
      : text_(std::make_unique<sf::Text>(font)), rect_(rect) {

    text_->setString(text);
    text_->setCharacterSize(font_size);
    text_->setFillColor(sf::Color::White);

    // Align text in the center
    auto text_center_local = text_->getLocalBounds().getCenter();
    auto body_center_global = rect.getCenter();
    sf::Vector2f text_position = body_center_global - text_center_local;
    text_->setPosition(text_position);

    body_.setSize(rect.getSize());
    body_.setPosition(rect_.getPosition());
    body_.setFillColor(sf::Color::Blue);
  }

  void Draw(sf::RenderWindow& window) {
    if (visible_) {
      window.draw(body_);
      window.draw(*text_);
    }
  }

  bool Contains(const sf::Vector2i& pos) {
    return rect_.contains({static_cast<float>(pos.x), static_cast<float>(pos.y)});
  }

 private:
  std::unique_ptr<sf::Text> text_;
  sf::Rect<float> rect_;
  sf::RectangleShape body_;
};

class Text : public Widget{
 public:
  Text() = default;
  Text(sf::Font& font, const std::string& text, const sf::Vector2f& position, unsigned font_size = 50)
     : text_(std::make_unique<sf::Text>(font)){

    text_->setString(text);
    text_->setCharacterSize(font_size);
    text_->setFillColor(sf::Color::Red);

    auto text_center_local = text_->getLocalBounds().getCenter();
    sf::Vector2f text_position = position - text_center_local;
  }

  void Draw(sf::RenderWindow& window) {
    if (visible_)
      window.draw(*text_);
  }

 private:
  std::unique_ptr<sf::Text> text_;
};

#endif //WHATEVERGAME_SOURCE_GAME_STATES_TEMP_GUI_H_
