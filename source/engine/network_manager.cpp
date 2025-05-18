#include "network_manager.h"

#include "network/network_common.h"
#include "network/sniffer.h"

#include <span>
#include <string>

void NetworkManager::StartServer(uint16_t port) {
  std::string command = server_path_ + " " + std::to_string(port);
  try {
    server_process_ = std::make_unique<TinyProcessLib::Process>(
        command, "",
        [](const char *bytes, size_t n) {
          std::cout << std::string(bytes, n);
        },
        [](const char *bytes, size_t n) {
          std::cerr << std::string(bytes, n);
        });

    std::cout << "Started server in the separate process." << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Failed to start process: " << e.what() << std::endl;
  }
}

void NetworkManager::StopServer() {
  if (server_process_){
    server_process_->kill(true);
    server_process_ = nullptr;
  }
}

void NetworkManager::SearchServers(const std::vector<int>& broadcasting_ports, uint32_t timeout) {
  for (int broadcasting_port : broadcasting_ports) {
    sniffers_.emplace_back(std::make_unique<Sniffer>(broadcasting_port));
    sniffers_.back()->Start(timeout, [&](std::string msg) {
      if (auto pos = msg.find(':'); pos != std::string::npos) {
        std::string host = msg.substr(0, pos);
        std::string port = msg.substr(pos + 1);
        available_servers_.emplace_back(host, port);
      } else {
        std::cerr << "[CLIENT] Error: sniffer sniffed something strange: " << msg << std::endl;
      }
    });
  }
}

void NetworkManager::OnReceive(std::shared_ptr<Message<GameEventType>> message) {
  on_receive_handler_(std::move(message));
}

std::vector<ServerAddress> NetworkManager::GetAvailableServer() {
  // Making a copy to ensure memory consistency
  mutex_.lock();
  auto servers = available_servers_;
  mutex_.unlock();
  return servers;
}
