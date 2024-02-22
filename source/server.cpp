#include "network/async_client.h"
#include "network/async_server.h"

#include <asio.hpp>
#include <exception>
#include <sstream>
#include <chrono>
#include <thread>

int CStrToInt(const char* str)
{
  std::stringstream ss;
  ss << str;

  int num;
  ss >> num;

  return num;
}

int main(int argc, char** argv)
{
  try {
    asio::io_context io_context;

    std::cout << "Starting up...";
    AsyncServer server(io_context, static_cast<short>(CStrToInt(argv[1])));
    std::cout << "Up and running.";

    io_context.run();
    std::this_thread::sleep_for(std::chrono::seconds(3));

  } catch( std::exception& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}