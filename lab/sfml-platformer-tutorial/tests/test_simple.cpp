#include <SFML/Window.hpp>
#include <iostream>

int main()
{
    std::cout << "Creating window..." << std::endl;
    sf::Window window(sf::VideoMode(sf::Vector2u(800, 600)), "Test");
    std::cout << "Window created!" << std::endl;
    
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    }
    return 0;
}
