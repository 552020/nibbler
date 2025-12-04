#include "World.hpp"
#include "TextBox.hpp"
#include <string>
#include <iostream>

World::World(sf::Vector2u l_windSize) {
    m_blockSize = 16;
    m_windowSize = l_windSize;
    RespawnApple();
    m_appleShape.setFillColor(sf::Color::Red);
    m_appleShape.setRadius(m_blockSize / 2);
    
    for (int i = 0; i < 4; ++i) {
        m_bounds[i].setFillColor(sf::Color(150, 0, 0));
        if (!((i + 1) % 2)) {
            m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
        } else {
            m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
        }
        
        if (i < 2) {
            m_bounds[i].setPosition(sf::Vector2f(0, 0));
        } else {
            m_bounds[i].setOrigin(m_bounds[i].getSize());
            m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
        }
    }
    
    // Alternative more readable version (commented out):
    // // Top wall
    // m_bounds[0].setFillColor(sf::Color(150, 0, 0));
    // m_bounds[0].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
    // m_bounds[0].setPosition(0, 0);
    //
    // // Left wall
    // m_bounds[1].setFillColor(sf::Color(150, 0, 0));
    // m_bounds[1].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
    // m_bounds[1].setPosition(0, 0);
    //
    // // Bottom wall
    // m_bounds[2].setFillColor(sf::Color(150, 0, 0));
    // m_bounds[2].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
    // m_bounds[2].setOrigin(m_bounds[2].getSize());
    // m_bounds[2].setPosition(sf::Vector2f(m_windowSize));
    //
    // // Right wall
    // m_bounds[3].setFillColor(sf::Color(150, 0, 0));
    // m_bounds[3].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
    // m_bounds[3].setOrigin(m_bounds[3].getSize());
    // m_bounds[3].setPosition(sf::Vector2f(m_windowSize));
}

World::~World() {
}

void World::RespawnApple() {
    int maxX = (m_windowSize.x / m_blockSize) - 2;
    int maxY = (m_windowSize.y / m_blockSize) - 2;
    m_item = sf::Vector2i(
        rand() % maxX + 1, rand() % maxY + 1);
    m_appleShape.setPosition(sf::Vector2f(
        m_item.x * m_blockSize,
        m_item.y * m_blockSize));
}

bool World::WouldHitWall(const sf::Vector2i& l_position, Direction l_dir) {
    int gridSize_x = m_windowSize.x / m_blockSize;
    int gridSize_y = m_windowSize.y / m_blockSize;
    
    sf::Vector2i nextPos = l_position;
    
    // Calculate next position based on direction
    if (l_dir == Direction::Left) {
        nextPos.x--;
    } else if (l_dir == Direction::Right) {
        nextPos.x++;
    } else if (l_dir == Direction::Up) {
        nextPos.y--;
    } else if (l_dir == Direction::Down) {
        nextPos.y++;
    } else {
        return false; // No direction, no movement
    }
    
    // Check if next position would hit wall
    return (nextPos.x <= 0 ||
            nextPos.y <= 0 ||
            nextPos.x >= gridSize_x - 1 ||
            nextPos.y >= gridSize_y - 1);
}

void World::Update(Snake& l_player, Textbox& l_textbox) {
    if (l_player.GetPosition() == m_item) {
        l_player.Extend();
        l_player.IncreaseScore();
        l_textbox.Add("Apple eaten! Score: " + std::to_string(l_player.GetScore()));
        RespawnApple();
    }
    
    int gridSize_x = m_windowSize.x / m_blockSize;
    int gridSize_y = m_windowSize.y / m_blockSize;
    
    sf::Vector2i pos = l_player.GetPosition();
    
    // Check for wall collision (after movement has occurred)
    if (pos.x <= 0 ||
        pos.y <= 0 ||
        pos.x >= gridSize_x - 1 ||
        pos.y >= gridSize_y - 1) {
        std::cout << "WALL COLLISION! Snake at (" << pos.x << ", " << pos.y 
                  << ") hit wall. Grid bounds: (" << gridSize_x << ", " << gridSize_y << ")" << std::endl;
        l_player.Lose();
    }
}

void World::Render(sf::RenderWindow& l_window) {
    for (int i = 0; i < 4; ++i) {
        l_window.draw(m_bounds[i]);
    }
    l_window.draw(m_appleShape);
}

int World::GetBlockSize() {
    return m_blockSize;
}

// SFML types and functions used in this file:
// - sf::Vector2u: 2D vector with unsigned int components (x, y), used for window sizes
// - sf::Vector2i: 2D vector with int components (x, y), used for grid positions (apple position)
// - sf::Vector2f: 2D vector with float components (x, y), used for sizes and positions in pixel coordinates
// - sf::RenderWindow: Window object used for rendering graphics, passed by reference to Render()
//   - draw(): Method to draw drawable objects (like sf::CircleShape, sf::RectangleShape) to the window
// - sf::CircleShape: Circle shape used for rendering the apple (m_appleShape)
//   - setFillColor(): Method to set the fill color of the shape
//   - setRadius(): Method to set the radius of the circle
//   - setPosition(): Method to set the position of the shape in pixel coordinates
// - sf::RectangleShape: Rectangle shape used for rendering boundary walls (m_bounds)
//   - setFillColor(): Method to set the fill color of the shape
//   - setSize(): Method to set the size of the rectangle
//   - setPosition(): Method to set the position of the shape in pixel coordinates
//   - setOrigin(): Method to set the origin point of the shape (used for positioning from corners)
//   - getSize(): Method to get the size of the rectangle
// - sf::Color: Color class for setting fill colors (Red for apple, dark red for walls)
