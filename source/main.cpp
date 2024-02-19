#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include "Player.hpp"

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

    Player pl({100, 100}, {100, 100}, "../textures/pidor.png");

    sf::RectangleShape* playerShape = pl.getShape();


    int i = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed ) {
                pl.moveRight();
            }

        }
        window.clear();
        window.draw(*playerShape);

        window.display();
    }
    return 0;
}
