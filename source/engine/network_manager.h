#ifndef WHATEVERGAME_SOURCE_ENGINE_NETWORK_MANAGER_H_
#define WHATEVERGAME_SOURCE_ENGINE_NETWORK_MANAGER_H_


#include "../network/network_components.h"


#include <thread>
#include <chrono>
#include <atomic>

class NetworkManager {
 public:
  NetworkManager(): server_(3000), client_(4000) {}

  void StartServer();

  void ConnectClient(const std::string& address, const std::string& port);

  void SendData(GameEventType t, float x, float y);

  std::shared_ptr<Packet<GameEventType>> ReceiveData();

  bool IsClient() const;

 private:
  bool is_client_= false;
  CustomClient client_;
  CustomServer server_;
};


#endif //WHATEVERGAME_SOURCE_ENGINE_NETWORK_MANAGER_H_
