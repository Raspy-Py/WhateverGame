#ifndef WHATEVERGAME_SOURCE_ENGINE_PLAY_STATE_H_
#define WHATEVERGAME_SOURCE_ENGINE_PLAY_STATE_H_

#include "engine/game_state.h"

#include "temp_gui.h"

class PlayState: public GameState {
 public:
  explicit PlayState(std::shared_ptr<Context> context);

  void Update(float delta_time) override;
  void Draw(sf::RenderWindow& window) override;

 private:
  void OnEntry() final;
  void OnExit() final;

 private:
  sf::RectangleShape player_rect_;
  sf::Vector2f player_position_;
  sf::Vector2f player_size_;

  Text text_;
  Button kill_server_btn_;
};

#endif //WHATEVERGAME_SOURCE_ENGINE_PLAY_STATE_H_
