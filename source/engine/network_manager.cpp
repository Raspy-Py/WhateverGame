#include "network_manager.h"

void NetworkManager::StartServer() {
  is_client_ = false;
  server_.Start();
}

void NetworkManager::ConnectClient(const std::string &address, const std::string &port) {
  is_client_ = true;
  client_.Connect(address, port);
}

void NetworkManager::SendData(GameEventType t, float x, float y) {
  Message<GameEventType> msg;
  msg.header.id = t;
  msg << x << y;
  client_.Send(msg);
}

std::shared_ptr<Packet<GameEventType>> NetworkManager::ReceiveData() {
  auto p = server_.PopPacket();
  return p;
}

bool NetworkManager::IsClient() const{
  return is_client_;
}