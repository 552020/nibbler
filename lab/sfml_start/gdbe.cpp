// This code is from the book "Game Development by Example"
// 
// NOTE: Updated for SFML 3.x API (book uses SFML 2.x):
// - VideoMode: Use initializer list {width, height} instead of (width, height)
// - pollEvent(): Returns std::optional<Event> instead of taking Event& parameter
// - Event checking: Use event->is<sf::Event::Closed>() instead of event.type == sf::Event::Closed
// - setPosition(): Use vector/initializer list {x, y} instead of separate x, y parameters
// - clear(): No longer requires color parameter (defaults to black)
//
#include <SFML/Graphics.hpp>
#include <optional>

int main() {
    sf::RenderWindow window(sf::VideoMode({640u, 480u}), "First window!");

    sf::RectangleShape rectangle(sf::Vector2f(128.0f, 128.0f));
    rectangle.setFillColor(sf::Color::Red);
    // rectangle.setPosition({128, 128});
    rectangle.setPosition({128.0f, 128.0f});
    sf::RectangleShape rectangle2(sf::Vector2f(128.0f, 128.0f));
    rectangle2.setFillColor(sf::Color::Blue);
    rectangle2.setPosition({0.0f, 0.0f});
    sf::RectangleShape rectangle3(sf::Vector2f(256.0f, 256.0f));
    rectangle3.setFillColor(sf::Color::White);
    rectangle3.setPosition({0.0f, 0.0f});
    sf::RectangleShape rectangle4(sf::Vector2f(128.0f, 128.0f));
    rectangle4.setFillColor(sf::Color::Yellow);
    rectangle4.setPosition({320.0f, 240.0f});
    rectangle4.setOrigin({64.0f, 64.0f});
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                // Close window button clicked.
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        // Draw here.
        window.draw(rectangle3);
        window.draw(rectangle);
        window.draw(rectangle2);
        window.draw(rectangle4);
        window.display();
    }

    return 0;
}

