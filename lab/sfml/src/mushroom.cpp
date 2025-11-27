#include <SFML/Graphics.hpp>
#include <optional>

int main() {
    sf::RenderWindow window(sf::VideoMode({640u, 480u}), "Bouncing mushroom.");
    
    sf::Texture mushroomTexture;
    if (!mushroomTexture.loadFromFile("assets/Mushroom.png")) {
        return 1; // Failed to load texture
    }
    
    sf::Sprite mushroom(mushroomTexture);
    sf::Vector2u size = mushroomTexture.getSize();
    mushroom.setOrigin({size.x / 2.0f, size.y / 2.0f});
    
    sf::Vector2f increment(0.1f, 0.1f);
    
    // Set initial position to center of window
    // mushroom.setPosition({320.0f, 240.0f});  // Old hardcoded approach
    sf::Vector2u windowSize = window.getSize();
    mushroom.setPosition({windowSize.x / 2.0f, windowSize.y / 2.0f});
    
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        
        if ((mushroom.getPosition().x + (size.x / 2.0f) > window.getSize().x && increment.x > 0) ||
            (mushroom.getPosition().x - (size.x / 2.0f) < 0 && increment.x < 0)) {
            // Reverse the direction on X axis.
            increment.x = -increment.x;
        }
        
        if ((mushroom.getPosition().y + (size.y / 2.0f) > window.getSize().y && increment.y > 0) ||
            (mushroom.getPosition().y - (size.y / 2.0f) < 0 && increment.y < 0)) {
            // Reverse the direction on Y axis.
            increment.y = -increment.y;
        }
        
        mushroom.setPosition(mushroom.getPosition() + increment);
        
        window.clear(sf::Color(16, 16, 16, 255)); // Dark gray.
        window.draw(mushroom); // Drawing our sprite.
        window.display();
    }
    
    return 0;
}

