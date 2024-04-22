
#ifndef WHATEVERGAME_SOURCE_NETWORK_NETWORK_COMPONENTS_H_
#define WHATEVERGAME_SOURCE_NETWORK_NETWORK_COMPONENTS_H_

#pragma once
#include "network/udp_client.h"
#include "network/udp_server.h"
#include "network/sniffer.h"
#include "network/broadcaster.h"


inline std::string find_local_ip() {
  asio::io_context io_context;
  std::string local_ip;
  try {
    asio::ip::tcp::resolver resolver(io_context);
    asio::ip::tcp::resolver::query query("8.8.8.8", "53");
    asio::ip::tcp::resolver::iterator endpoints = resolver.resolve(query);
    asio::ip::tcp::endpoint ep = *endpoints;
    asio::ip::tcp::socket socket(io_context);
    socket.connect(ep);
    local_ip = socket.local_endpoint().address().to_string();
    socket.close();
  } catch (std::exception& e) {
    std::cerr << "Could not find local IP: " << e.what() << '\n';
  }
  return local_ip;
}


enum class GameEventType{
  Default = 0,
  MovePlayer = 1,
};

inline std::atomic_bool finished = false;

class CustomClient : public UDPClient<GameEventType>{
 public:
  CustomClient(uint16_t port) : UDPClient<GameEventType>(port) {}
  ~CustomClient() override{
    Disconnect();
  }

  void OnReceive(std::shared_ptr<Message<GameEventType>> msg) override{
    std::cout << "[CLIENT] Server responded to the greetings" << std::endl;
  }
};

class CustomServer : public UDPServer<GameEventType>{
 public:
  explicit CustomServer(uint16_t port) : UDPServer<GameEventType>(port){}
  ~CustomServer() override{
    std::cout << "[SERVER] Shutting down..." << std::endl;
    Stop();
  }

  void OnReceive(Packet<GameEventType> packet) override{
    auto endp = packet.endpoint;
    std::cout << "[SERVER] Received greetings from: " << endp.address().to_string()
              << ":" << endp.port() << std::endl;

    SendToAllExcept({});
    finished = true;
  }
};

#endif //WHATEVERGAME_SOURCE_NETWORK_NETWORK_COMPONENTS_H_
