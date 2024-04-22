#ifndef WHATEVERGAME_SOURCE_ENGINE_PLAY_STATE_H_
#define WHATEVERGAME_SOURCE_ENGINE_PLAY_STATE_H_

#include "game_state.h"



class PlayState: public GameState {
 public:
  explicit PlayState(std::shared_ptr<Context> context);


  void Update(float delta_time) override;

  void Draw(sf::RenderWindow& window) override;

 private:
  // TODO: Player class
  sf::RectangleShape player_rect_;
  sf::Vector2f player_position_;
  sf::Vector2f player_size_;

  sf::RectangleShape player_rect2_;
  sf::Vector2f player_position2_;
  sf::Vector2f player_size2_;

};

#endif //WHATEVERGAME_SOURCE_ENGINE_PLAY_STATE_H_
