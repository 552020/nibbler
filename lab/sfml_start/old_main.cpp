#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

int main()
{
    try {
        // Create the main window
        sf::RenderWindow window(sf::VideoMode({800u, 600u}), "SFML Window");

        // Load a texture
        sf::Texture texture;
        if (!texture.loadFromFile("assets/cabinet.jpg"))
        {
            std::cerr << "Error: Failed to load texture from assets/cabinet.jpg" << std::endl;
            std::cerr << "Current directory: " << std::filesystem::current_path() << std::endl;
            return 1;
        }
        sf::Sprite sprite(texture);

        // Load a font
        sf::Font font;
        if (!font.openFromFile("assets/arial/ARIAL.TTF"))
        {
            std::cerr << "Error: Failed to load font from assets/arial/ARIAL.TTF" << std::endl;
            return 1;
        }
    sf::Text text(font, "Hello SFML", 50);
    text.setPosition({10, 10});
    text.setFillColor(sf::Color::White);

    // Main loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear, draw, display
        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.display();
    }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

