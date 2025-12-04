#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

int main()
{
    std::cout << "Before window creation" << std::endl;
    std::cout.flush();
    
    // Try with minimal settings
    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "Test");
    
    std::cout << "Window created!" << std::endl;
    std::cout.flush();
    
    window.close();
    return 0;
}
