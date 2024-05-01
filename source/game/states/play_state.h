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
  void OnReceiveHandler(std::shared_ptr<Message<GameEventType>>&& message);

 private:
  uint32_t passport_;
  std::atomic_bool server_accepted_connection_ = false;
  sf::RectangleShape player_rect_;
  std::mutex mutex_;
  std::unordered_map<uint32_t, sf::RectangleShape> other_players_;

  Text text_;
  Button kill_server_btn_;

  static constexpr sf::Vector2f player_size = {50.f, 50.f};
};

#endif //WHATEVERGAME_SOURCE_ENGINE_PLAY_STATE_H_
