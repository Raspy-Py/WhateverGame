#ifndef WHATEVERGAME_SOURCE_NETWORK_BROADCASTER_H_
#define WHATEVERGAME_SOURCE_NETWORK_BROADCASTER_H_

#include <cstdint>
#include "asio.hpp"
#include <thread>
#include <iostream>

class Broadcaster {
  using udp = asio::ip::udp;
 public:
  explicit Broadcaster(const std::vector<uint16_t>& broadcast_ports, uint32_t cooldown = 200)
      : io_context_(),
        cooldown_(cooldown),
        socket_(io_context_, udp::endpoint(udp::v4(), 0)){
    socket_.set_option(asio::socket_base::broadcast(true));

    for (uint16_t port : broadcast_ports)
      endpoints_.emplace_back(asio::ip::address_v4::broadcast(), port);
  }

  ~Broadcaster(){
    StopBroadcasting();
  }

  void StartBroadcasting(const std::string& message, std::function<void(void)>&& user_callback = []{}){
    if (!message.empty() && message.size() > kMaxMessageSize) {
      std::cerr << "Broadcaster error: message size should be (0, " << kMaxMessageSize << "). " << std::endl;
      return;
    }
    user_callback_ = std::move(user_callback);
    message_ = message;
    for (auto& endpoint : endpoints_)
      StartSend(endpoint);
    context_thread_ = std::thread([&]{io_context_.run();});
  }

  void StopBroadcasting(){
    io_context_.stop();

    if (context_thread_.joinable())
      context_thread_.join();
  }

 private:
  void StartSend(const udp::endpoint& endpoint){
    socket_.async_send_to(
      asio::buffer(message_), endpoint,
      [&](asio::error_code ec, size_t bytes_sent){
        if (!ec){
          Callback();
          StartSend(endpoint);
        }else{
          std::cerr << "Broadcaster error: failed to send message." << std::endl;
        }
      });
  }

 private:
  void Callback(){
    std::this_thread::sleep_for(std::chrono::milliseconds(cooldown_));
    user_callback_();
  }

 private:
  // Context should always go first
  asio::io_context io_context_;
  std::thread context_thread_;

  udp::socket socket_;
  std::vector<udp::endpoint> endpoints_;
  std::function<void(void)> user_callback_ = []{};

  std::string message_;
  uint32_t cooldown_;

  // Should be the same as Sniffer's buffer size
  static constexpr size_t kMaxMessageSize = 128;
};

#endif //WHATEVERGAME_SOURCE_NETWORK_BROADCASTER_H_