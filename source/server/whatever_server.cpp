#include "whatever_server.h"

// Returns device's IP in the local network.
// Useful for client-server discovery algorithm.
std::string FindLocalIP() {
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


WhateverServer::~WhateverServer() {
  std::cout << "[SERVER] Shutting down..." <<
  std::endl;
  Stop();
}

void WhateverServer::OnReceive(Packet<GameEventType> packet) {
  auto endp = packet.endpoint;
  std::cout << "[SERVER] Received greetings from: " << endp.address().to_string()
            << ":" << endp.port() << std::endl;

  SendToAllExcept({});

  // For now, I want to shut down the server, when it receives the greetings from the client
  {
    std::lock_guard<std::mutex> lk(cv_mutex_);
    received_greetings_ = true;
  }
  cv_.notify_one();
}

void WhateverServer::StartBroadcasting(){
  auto msg = FindLocalIP() + ":" + std::to_string(port_);
  // For now send server cords only once
  Broadcaster::StartBroadcasting(msg, [this]{ is_broadcasting_ = false;});
}

void WhateverServer::Join(){
  std::unique_lock<std::mutex> lk(cv_mutex_);
  cv_.wait(lk, [this]{ return received_greetings_.load(); });
  StopBroadcasting();
}