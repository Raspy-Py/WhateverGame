#include "network/async_client.h"
#include "network/async_server.h"

#include <exception>
#include <chrono>
#include <thread>

#include <asio.hpp>
#include <process.hpp>

using TinyProcessLib::Process;

int main(int argc, char** argv)
{
  try {
    asio::io_context io_context;
    Process process(
      "Server.exe 8080", "",
      [](const char *bytes, size_t n) {
        std::cout << "[SERVER]: " << std::string(bytes, n) << std::endl;
      },
      [](const char *bytes, size_t n) {
        std::cout << "[SERVER]: " << std::string(bytes, n) << std::endl;
      });

    // Give the server time to start
    std::this_thread::sleep_for(std::chrono::seconds(3));

    AsyncClient client(io_context, "localhost", "8080");
    for (int i = 0; i < 10; ++i) {
      client.Send(std::string("msg #") + std::to_string(i));
    }
    client.Send("kill");
    io_context.run();

    std::cout << "Server process exited with code: " << process.get_exit_status() << std::endl;
  } catch( std::exception& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}