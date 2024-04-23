#ifndef WHATEVERGAME_SOURCE_ENGINE_NETWORK_MANAGER_H_
#define WHATEVERGAME_SOURCE_ENGINE_NETWORK_MANAGER_H_

#include "network/common.h"
#include "process.hpp"

#include <thread>
#include <chrono>
#include <atomic>

class NetworkManager {
 public:
  NetworkManager();

  void StartServer();

  void ConnectClient(const std::string& address, const std::string& port);

  void SendData(T t, float x, float y);

  std::shared_ptr<Packet<T>> ReceiveData();
};

template<typename T>
NetworkManager<T>::NetworkManager() {

}

template<typename T>
void NetworkManager<T>::StartServer() {
  std::string executable_path = "./WhateverGame"; // Path to the executable
  std::string port = "8080"; // Port number as a string

  std::string command = executable_path + " " + port;

  try {
    TinyProcessLib::Process process(
        command, "",
        [](const char *bytes, size_t n) { // This is the read_stdout function
          std::cout << std::string(bytes, n);
        },
        [](const char *bytes, size_t n) { // This is the read_stderr function
          std::cerr << std::string(bytes, n);
        });

    std::cout << "Started server in the separate process." << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Failed to start process: " << e.what() << std::endl;
  }
}

template<typename T>
void NetworkManager<T>::ConnectClient(const std::string &address, const std::string &port) {
  //is_client_ = true;
  //client_.Connect(address, port);
}

template<typename T>
void NetworkManager<T>::SendData(T t, float x, float y) {
  Message<T> msg;
  msg.header.id = t;
  msg << x << y;

  //client_.Send(msg);
}
template<typename T>
std::shared_ptr<Packet<T>> NetworkManager<T>::ReceiveData() {
  //auto p = server_.PopPacket();
  return {};
}


#endif //WHATEVERGAME_SOURCE_ENGINE_NETWORK_MANAGER_H_