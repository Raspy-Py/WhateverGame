#ifndef WHATEVERGAME_SOURCE_NETWORK_UDPSERVER_H_
#define WHATEVERGAME_SOURCE_NETWORK_UDPSERVER_H_

#include <memory>
#include <cstdint>
#include "asio.hpp"

#include "network_common.h"
#include "thread_safe_queue.h"

template <typename T>
class UDPServer {
  using udp = asio::ip::udp;

  struct ClientEntry{
    udp::endpoint endpoint;
    uint32_t id = -1;
  };

 public:
  UDPServer(uint16_t port)
      : io_context_(),
      socket_(io_context_, udp::endpoint(udp::v4(), port)),
      recv_buffer_(kMaxMsgSize),
      send_buffer_(kMaxMsgSize),
      client_uid_(0) {}

  virtual ~UDPServer(){
    Stop();
  }

  void Start(){
    recv_buffer_.resize(kMaxMsgSize);
    send_buffer_.resize(kMaxMsgSize);

    StartReceive();
    context_thread_ = std::thread([this]{ io_context_.run(); });
  }

  void Stop(){
    if (io_context_.stopped()) return;
    io_context_.stop();

    if (context_thread_.get_id() == std::this_thread::get_id()) {
      context_thread_.detach();
    } else {
      if (context_thread_.joinable())
        context_thread_.join();
    }
  }

  virtual void OnReceive(Packet<T> packet) = 0;

  void SendToExact(const Message<T>& msg, const udp::endpoint& endpoint) {
    out_queue_.Push({
      endpoint,
      std::make_shared<Message<T>>(msg)
    });
  }

  void SendToAllExcept(const Message<T>& msg, uint32_t ignore_id = -1){
    auto msg_ptr = std::make_shared<Message<T>>(msg);
    for (auto& [address, client_entry] : clients_map_) {
      if (client_entry.id != ignore_id)
        out_queue_.Push({client_entry.endpoint, msg_ptr});
    }
    HandleSend();
  }

  void ForgetClient(const asio::ip::address& address){
    clients_map_.erase(address);
  }

  std::unordered_map<asio::ip::address, ClientEntry>& clients_map(){
    return clients_map_;
  }

 private:
  void HandleSend(){
    Packet<T> packet;
    if (!out_queue_.TryPop(packet)) return;
    packet.message->Serialize(send_buffer_);
    socket_.async_send_to(
      asio::buffer(send_buffer_), packet.endpoint,
      [this](const asio::error_code& ec, std::size_t bytes_sent){
        if (!out_queue_.Empty())
          HandleSend();
      });
  }

  void StartReceive(){
    socket_.async_receive_from(
      asio::buffer(recv_buffer_), remote_endpoint_,
      [this](const asio::error_code&, std::size_t bytes_recvd){
        // if it's a first message from this client, record the endpoint
        auto [it, inserted] = clients_map_.try_emplace(remote_endpoint_.address());
        if (inserted)
          it->second = {remote_endpoint_, client_uid_++};
        else
          it->second.endpoint = remote_endpoint_;

        recv_buffer_.resize(bytes_recvd);
        auto msg = std::make_shared<Message<T>>();
        msg->Deserialize(recv_buffer_, bytes_recvd);
        in_queue_.Push({ remote_endpoint_, msg });
        HandleReceive();
      });
  }

  void HandleReceive(){
    if (io_context_.stopped())
      return;

    Packet<T> packet;
    in_queue_.WaitAndPop(packet);
    OnReceive(packet);
    StartReceive();
  }

 private:
  asio::io_context io_context_;
  udp::socket socket_;
  std::thread context_thread_;

  udp::endpoint remote_endpoint_;

  ThreadSafeQueue<Packet<T>> in_queue_;
  ThreadSafeQueue<Packet<T>> out_queue_;

  std::unordered_map<asio::ip::address, ClientEntry> clients_map_;
  uint32_t client_uid_;

  static constexpr size_t kMaxMsgSize = 1024;
  std::vector<char> recv_buffer_;
  std::vector<char> send_buffer_;
};

#endif //WHATEVERGAME_SOURCE_NETWORK_UDPSERVER_H_