#include "network/async_client.h"
#include "network/async_server.h"

#include <asio.hpp>
#include <exception>

int main(int argc, char** argv)
{
  try {
    asio::io_context io_context;
    AsyncServer server(io_context, 8080);
    AsyncClient client(io_context, "localhost", "8080");
    client.Send("Yo, what's up?");
    io_context.run();
  } catch( std::exception& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}