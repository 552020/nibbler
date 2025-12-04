#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    std::cout << "Starting..." << std::endl;
    
    std::cout << "Creating window..." << std::endl;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");
    std::cout << "Window created successfully!" << std::endl;
    
    std::cout << "Entering loop..." << std::endl;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        window.clear();
        window.display();
    }
    
    std::cout << "Exiting..." << std::endl;
    return 0;
}


