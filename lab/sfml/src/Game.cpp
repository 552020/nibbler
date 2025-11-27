#include "Game.hpp"

// SFML 3.x change: Sprite no longer has a default constructor
// In SFML 2.x: sf::Sprite sprite; sprite.setTexture(texture); (default constructor + setTexture)
// In SFML 3.x: sf::Sprite sprite(texture); (must construct with texture)
// Solution: Use sf::Texture constructor that loads from file - clean RAII pattern
// Game::Game() : m_window("Chapter 2", sf::Vector2u(800, 600)) {
Game::Game() 
: m_window("Chapter 2", sf::Vector2u(800, 600))
, m_mushroomTexture("assets/Mushroom.png")  // SFML 3.x: Texture constructor loads from file
, m_mushroom(m_mushroomTexture)            // Sprite constructed with loaded texture
{
    m_increment = sf::Vector2i(4, 4);
    
    // Set initial position for mushroom (center of window)
    sf::Vector2u windowSize = m_window.GetWindowSize();
    sf::Vector2u textureSize = m_mushroomTexture.getSize();
    m_mushroom.setPosition({
        (windowSize.x - textureSize.x) / 2.0f,
        (windowSize.y - textureSize.y) / 2.0f
    });
}

Game::~Game() {
}

void Game::Update() {
    m_window.Update(); // Update window events.
    MoveMushroom();
}

void Game::MoveMushroom() {
    sf::Vector2u l_windSize = m_window.GetWindowSize();
    sf::Vector2u l_textSize = m_mushroomTexture.getSize();

    if ((m_mushroom.getPosition().x > l_windSize.x - l_textSize.x && m_increment.x > 0) ||
        (m_mushroom.getPosition().x < 0 && m_increment.x < 0)) {
        m_increment.x = -m_increment.x;
    }

    if ((m_mushroom.getPosition().y > l_windSize.y - l_textSize.y && m_increment.y > 0) ||
        (m_mushroom.getPosition().y < 0 && m_increment.y < 0)) {
        m_increment.y = -m_increment.y;
    }

    m_mushroom.setPosition({
        m_mushroom.getPosition().x + m_increment.x,
        m_mushroom.getPosition().y + m_increment.y
    });
}

void Game::HandleInput() {
    // Handle input logic here (can be empty for now)
}

void Game::Render() {
    m_window.BeginDraw();
    m_window.Draw(m_mushroom);
    m_window.EndDraw();
}

Window* Game::GetWindow() {
    return &m_window;
}

