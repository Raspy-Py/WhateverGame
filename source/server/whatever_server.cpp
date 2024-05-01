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
    std::cerr << "[SERVER] Error: Could not find local IP: " << e.what() << '\n';
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

  switch (packet.message->header.id){
    case GameEventType::ClientRequestConnect: {
      uint32_t client_id = clients_map()[packet.endpoint];
      players_data_[client_id] = {}; // Initialize default player data structure

      // Send the client its passport id
      Message<GameEventType> msg;
      msg.header.id = GameEventType::ServerApproveConnection;
      msg << client_id;
      SendToExact(msg, packet.endpoint);
      break;
    }
    case GameEventType::ClientDisconnect: {
      uint32_t client_id = clients_map()[packet.endpoint];
      players_data_.erase(client_id);

      ForgetClient(packet.endpoint);
      break;
    }
    case GameEventType::ClientUpdatePosition: {
      auto& msg = *(packet.message);

      PlayerInfo player_info;
      uint32_t client_id;
      msg >> player_info >> client_id;

      players_data_[client_id] = player_info;

      // TODO: THIS IS SUPER STRANGE ASYNCHRONOUS TICKLESS APPROACH
      Message<GameEventType> server_msg;
      server_msg.header.id = GameEventType::ServerUpdateNetworkData;
      server_msg << client_id << player_info;
      SendToAllExcept(server_msg, client_id);
      break;
    }
    case GameEventType::ClientRequestServerShutdown: {
      uint32_t client_id = clients_map()[packet.endpoint];
      if (client_id == 0){ // Thus, it's been sent by server owner
        Message<GameEventType> msg;
        msg.header.id = GameEventType::ServerNotifyShutdown;
        SendToAllExcept(msg, client_id);

        FireStopSignal();
      }
      break;
    }
    default: break;
  };
}

void WhateverServer::StartBroadcasting(){
  auto msg = FindLocalIP() + ":" + std::to_string(port_);
  Broadcaster::StartBroadcasting(msg);
}

void WhateverServer::WaitForStopSignal(){
  std::unique_lock<std::mutex> lk(cv_mutex_);
  cv_.wait(lk, [this]{ return should_shutdown_.load(); });
}
void WhateverServer::FireStopSignal() {
  // Notify main thread to stop the server
  should_shutdown_ = true;
  cv_.notify_one();
}
