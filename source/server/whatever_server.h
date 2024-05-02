#ifndef WHATEVERGAME_SOURCE_MULTIPLAYER_WHATEVERSERVER_H_
#define WHATEVERGAME_SOURCE_MULTIPLAYER_WHATEVERSERVER_H_

#include "engine/network_event.h"
#include "engine/network/network_common.h"
#include "engine/network/udp_server.h"
#include "engine/network/broadcaster.h"

#include <condition_variable>
#include <atomic>

class WhateverServer : public UDPServer<GameEventType>, public Broadcaster {
  struct PlayerInfo{
    float x;
    float y;
  };

 public:
  explicit WhateverServer(uint16_t server_port, const std::vector<uint16_t> broadcast_ports)
      : UDPServer<GameEventType>(server_port),
        Broadcaster(broadcast_ports),
        port_(server_port) {}

  ~WhateverServer() override;

  void OnReceive(Packet<GameEventType> packet) override;
  void StartBroadcasting();
  void WaitForStopSignal();

 private:
  void FireStopSignal();

 private:
  // Game logic stuff
  std::unordered_map<uint32_t, PlayerInfo> players_data_;

  // Operational mess
  uint16_t port_;
  std::mutex cv_mutex_;
  std::condition_variable cv_;
  std::atomic_bool should_shutdown_ = false;
};

#endif //WHATEVERGAME_SOURCE_MULTIPLAYER_WHATEVERSERVER_H_
