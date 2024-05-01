#ifndef WHATEVERGAME_SOURCE_NETWORK_SNIFFER_H_
#define WHATEVERGAME_SOURCE_NETWORK_SNIFFER_H_

#include <cstdint>
#include <functional>
#include <iostream>

#include "asio.hpp"

class Sniffer {
  using udp = asio::ip::udp;

 public:
  Sniffer(uint16_t broadcast_port)
      : io_context_(), socket_(io_context_, udp::endpoint(udp::v4(), broadcast_port)), timer_(io_context_) {}

  ~Sniffer() {
    Stop();
  }

  void Start(int timeout_seconds, std::function<void(const std::string&)>&& callback){
    callback_ = std::move(callback);
    StartReceive();
    SetTimeout(timeout_seconds);
    context_thread_ = std::thread([&]{ io_context_.run(); });
  }

  void Stop(){
    if (io_context_.stopped()) return; // Prevent multiple stops
    io_context_.stop();

    if (context_thread_.get_id() == std::this_thread::get_id()) {
      context_thread_.detach();
    } else {
      if (context_thread_.joinable())
        context_thread_.join();
    }
  }

 private:
  void StartReceive(){
    socket_.async_receive_from(
        asio::buffer(buffer_), sender_endpoint_,
        [&](const std::error_code& error, std::size_t bytes_recvd) {
          if (!error && bytes_recvd > 0) {
            timer_.cancel();  // Cancel the timer upon successful receipt
            std::string message(buffer_.data(), bytes_recvd);
            callback_(message);
            StartReceive();  // Continue receiving
          } else if (!error) {
            StartReceive();
          }
        });
  }

  void SetTimeout(int timeout_seconds) {
    timer_.expires_from_now(std::chrono::seconds(timeout_seconds));
    timer_.async_wait([this](const std::error_code &error) {
      if (!error) {
        std::cout << "[CLIENT]: Sniffer timeout." << std::endl;
        Stop();
      } else {
        if (error == asio::error::operation_aborted) {
          std::cout << "[CLIENT]: Timer was cancelled." << std::endl;
        } else {
          std::cout << "[CLIENT]: Error: " << error.message() << std::endl;
        }
      }
    });
  }

 private:
  asio::io_context io_context_;
  std::thread context_thread_;

  udp::socket socket_;
  udp::endpoint sender_endpoint_;
  asio::steady_timer timer_;
  std::function<void(const std::string&)> callback_;

  static constexpr size_t kBufferSize = 128;
  std::array<char, kBufferSize> buffer_;
};

#endif //WHATEVERGAME_SOURCE_NETWORK_SNIFFER_H_