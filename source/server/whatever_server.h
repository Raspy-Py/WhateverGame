#ifndef WHATEVERGAME_SOURCE_MULTIPLAYER_WHATEVERSERVER_H_
#define WHATEVERGAME_SOURCE_MULTIPLAYER_WHATEVERSERVER_H_

#include "engine/network/common.h"
#include "engine/network/udp_server.h"
#include "engine/network/broadcaster.h"

#include <condition_variable>

// This enum is duplicated for both server and client targets
enum class GameEventType{
  Default = 0
};

class WhateverServer : public UDPServer<GameEventType>, public Broadcaster {
 public:
  explicit WhateverServer(uint16_t server_port, uint16_t broadcast_port)
      : UDPServer<GameEventType>(server_port),
        Broadcaster(broadcast_port),
        port_(server_port) {}

  ~WhateverServer() override;

  void OnReceive(Packet<GameEventType> packet) override;

  void StartBroadcasting();

  void Join();

 private:
  // TODO: clean up this junk
  std::condition_variable cv_;
  std::mutex cv_mutex_;
  bool is_broadcasting_ = false;
  bool received_greetings_ = false;
  uint16_t port_;
};

#endif //WHATEVERGAME_SOURCE_MULTIPLAYER_WHATEVERSERVER_H_
