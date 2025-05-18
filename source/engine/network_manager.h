#ifndef WHATEVERGAME_SOURCE_ENGINE_NETWORK_MANAGER_H_
#define WHATEVERGAME_SOURCE_ENGINE_NETWORK_MANAGER_H_

#include "process.hpp"
#include "network_event.h"
#include "network/network_common.h"
#include "network/udp_client.h"
#include "network/sniffer.h"

#include <span>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>

class NetworkManager : public UDPClient<GameEventType> {
  using message_ptr = std::shared_ptr<Message<GameEventType>>;
 public:
  NetworkManager(const std::string &server_path)
      : UDPClient<GameEventType>(),
        server_path_(server_path),
        on_receive_handler_([](message_ptr&&){}){}
  ~NetworkManager() override { Disconnect(); }

  /*
   * Server control
   */
  void StartServer(uint16_t port);

  // By design the server should be running indefinitely, unless
  // some kind of agreed event occurs, but it can be forcefully
  // shut down by calling this method
  void StopServer();

  /*
   * Client control
   */
  // Searches for available servers in the local network
  void SearchServers(const std::vector<int>& broadcasting_ports, uint32_t timeout);

  // Callback for processing received messages
  void OnReceive(std::shared_ptr<Message<GameEventType>> message) override;

  // Set custom OnReceive handler
  void SetOnReceiveHandler(std::function<void(message_ptr&&)>&& handler) { on_receive_handler_ = std::move(handler); }

  // Returns a copy of the vector with available servers
  std::vector<ServerAddress> GetAvailableServer();

 private:
  std::function<void(message_ptr&& message)> on_receive_handler_;

  // Operational stuff
  std::string server_path_;
  std::unique_ptr<TinyProcessLib::Process> server_process_;

  std::mutex mutex_;
  std::vector<ServerAddress> available_servers_;
  std::vector<std::unique_ptr<Sniffer>> sniffers_;
};

#endif //WHATEVERGAME_SOURCE_ENGINE_NETWORK_MANAGER_H_