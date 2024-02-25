#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include "Player.hpp"
#include "Menu.hpp"

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

std::vector<char> Buffer(20 * 1024);

void ReadData(asio::ip::tcp::socket& socket)
{
    socket.async_read_some(asio::buffer(Buffer.data(), Buffer.size()),
                           [&](std::error_code ec, std::size_t length){
        if (!ec)
        {
            std::cout << "\nRead " << length << "bytes\n\n";
            for (size_t i = 0; i < length; ++i) {
                std::cout << Buffer[i];
            }

            ReadData(socket);
        }
    });
}


int main()
{
  asio::error_code ec;
  asio::io_context context;
  asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec), 80);
  asio::ip::tcp::socket socket(context);
  socket.connect(endpoint);

  if(!ec)
  {
      std::cout << "Connected!" << std::endl;
  }
  else
  {
      std::cout << "Failed to connect! Error: " << ec.message() << std::endl;
  }

  std::string request = "GET /index.html HTTP/1.1\r\n"
                        "Host: example.com\r\n"
                        "Connection: close\r\n\r\n";

  socket.write_some(asio::buffer(request.data(), request.size()), ec);
  ReadData(socket);


  // Use the VideoMode object to create a Window
  auto vm = sf::VideoMode::getDesktopMode();
  sf::RenderWindow window(vm, "Window Title");
  sf::Font font;
  if ( !font.loadFromFile("../assets/fonts/IdealGothic Bold.otf") ) {
    std::cerr << "Error while loading font\n";
  }
  Menu menu(vm.size.x, vm.size.y, font);

  Player pl({100, 100}, {100, 100},
            "../assets/textures/test.png");

  sf::RectangleShape* playerShape = pl.getShape();


  bool menu_flag = true;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
          window.close();

      if (event.type == sf::Event::KeyPressed ) {
        if (event.key.code == sf::Keyboard::Key::Up && menu_flag) {
          menu.MoveUp();
        }
        if (event.key.code == sf::Keyboard::Key::Down && menu_flag) {
          menu.MoveDown();
        }
        if (event.key.code == sf::Keyboard::Key::Enter && menu_flag) {
          int pressed = menu.pressed();
          switch (pressed) {
            case 0:
              std::cout << "Host the game\n";
              menu_flag = false;
              break;
            case 1:
              std::cout << "Joim the game\n";
              menu_flag = false;
              break;
            case 2:
              std::cout << "Exit...\n";
              window.close();

              break;
          }
        }
        if (event.key.code == sf::Keyboard::Key::Right && !menu_flag) {
          pl.moveRight();
        }
      }

    }
    window.clear();
    if ( menu_flag ) menu.draw(window);
    else window.draw(*playerShape);

    window.display();
  }
  return 0;
}
