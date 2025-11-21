#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    std::puts("=== Starting SFML test ===");
    std::puts("Before RenderWindow construction");
    std::fflush(stdout);
    
    try {
        // Create the main window (matching SFML example style)
        std::puts("About to create RenderWindow...");
        std::fflush(stdout);
        sf::RenderWindow window(sf::VideoMode({800u, 600u}), "SFML window", sf::Style::Titlebar | sf::Style::Close);
        std::puts("After RenderWindow construction - SUCCESS!");
        std::fflush(stdout);
        window.setFramerateLimit(60); // Limit to 60 FPS
        std::cout << "Window created" << std::endl;

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("assets/cabinet.jpg"))
    {
        std::cerr << "Failed to load texture" << std::endl;
        return 1;
    }
    std::cout << "Texture loaded" << std::endl;
    sf::Sprite sprite(texture);
    // Scale sprite to fit window if needed
    float scaleX = 800.0f / texture.getSize().x;
    float scaleY = 600.0f / texture.getSize().y;
    float scale = std::min(scaleX, scaleY);
    sprite.setScale({scale, scale});
    sprite.setPosition({0, 0});

    // Create a graphical text to display
    sf::Font font;
    if (!font.openFromFile("assets/arial/ARIAL.TTF"))
    {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }
    std::cout << "Font loaded" << std::endl;
    sf::Text text(font, "Hello SFML", 50);
    text.setPosition({10, 10});
    text.setFillColor(sf::Color::White);
    std::cout << "Text created" << std::endl;

    // Load a music to play (optional - only play if file exists)
    sf::Music music;
    if (music.openFromFile("nice_music.ogg"))
    {
    music.play();
        std::cout << "Music playing" << std::endl;
    }
    else
    {
        std::cout << "Music file not found (optional)" << std::endl;
    }

    std::cout << "Starting game loop" << std::endl;
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
    }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}