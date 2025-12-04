#pragma once

#include <SFML/Graphics.hpp>
#include "Snake.hpp"

enum class Direction;

class Textbox;

class World {
public:
    World(sf::Vector2u l_windSize);
    ~World();

    int GetBlockSize();
    void RespawnApple();
    void Update(Snake& l_player, Textbox& l_textbox);
    bool WouldHitWall(const sf::Vector2i& l_position, Direction l_dir);
    void Render(sf::RenderWindow& l_window);

private:
    sf::Vector2u m_windowSize;
    sf::Vector2i m_item;
    int m_blockSize;
    sf::CircleShape m_appleShape;
    sf::RectangleShape m_bounds[4];
};

// SFML types used in this file:
// - sf::Vector2u: 2D vector with unsigned int components (x, y), used for window sizes
// - sf::Vector2i: 2D vector with int components (x, y), used for grid positions (apple position)
// - sf::RenderWindow: Window object used for rendering graphics, passed by reference to Render()
// - sf::CircleShape: Circle shape used for rendering the apple (m_appleShape)
// - sf::RectangleShape: Rectangle shape used for rendering boundary walls (m_bounds)
