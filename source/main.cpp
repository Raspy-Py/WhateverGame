#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <asio.hpp>

int main()
{
    // Use the VideoMode object to create a Window
    auto vm = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(vm, "Window Title");
    sf::CircleShape circle(30);
    circle.setPosition({100, 100});
    circle.setFillColor({255,255,0,255});

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            window.clear();
            window.draw(circle);
            window.display();
        }
    }
    return 0;
}
