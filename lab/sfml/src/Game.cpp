#include "Game.hpp"
#include <ctime>
#include <string>
#include <iostream>
#include <cerrno>

Game::Game()
: m_window("Snake", sf::Vector2u(800, 600))
, m_world(sf::Vector2u(800, 600))
, m_snake(m_world.GetBlockSize())
, m_sprite(m_texture)
{
    m_textbox.Setup(5, 14, 350, sf::Vector2f(225, 0));
    m_textbox.Add("Seeded random number generator with: " + std::to_string(time(NULL)));
    
    // Texture and sprite setup.
    m_textureLoaded = m_texture.loadFromFile("assets/Mushroom.png");
    if (!m_textureLoaded) {
        std::cerr << "Failed to load texture from assets/Mushroom.png" << std::endl;
    } else {
        std::cout << "Texture loaded successfully. Mushroom sprite initialized." << std::endl;
        std::cout << "Texture size: " << m_texture.getSize().x << "x" << m_texture.getSize().y << std::endl;
        // Update sprite texture after loading (this should fix the 0x0 bounds issue)
        m_sprite.setTexture(m_texture, true);  // true = reset texture rect
        // Scale sprite down to 16x16 (1/8 of original size)
        m_sprite.setScale(sf::Vector2f(0.125f, 0.125f));
        // Position at center of window
        m_sprite.setPosition(sf::Vector2f(400.0f, 300.0f));
        // Get sprite bounds for debugging
        sf::FloatRect bounds = m_sprite.getGlobalBounds();
        std::cout << "Mushroom sprite positioned at (400, 300)" << std::endl;
        std::cout << "Sprite global bounds: (" << bounds.position.x << ", " << bounds.position.y 
                  << ") size: " << bounds.size.x << "x" << bounds.size.y << std::endl;
    }
    
    m_window.GetEventManager()->AddCallback("Move",
                                            &Game::MoveSprite, this);
}

Game::~Game() {
}

void Game::Update() {
    m_window.Update(); // Update window events.
    
    float timestep = 1.0f / m_snake.GetSpeed();
    if (m_elapsed.asSeconds() >= timestep) {
        m_snake.Tick();
        m_world.Update(m_snake, m_textbox);
        m_elapsed -= sf::seconds(timestep);
        
        if (m_snake.HasLost()) {
            m_textbox.Add("Game Over! Final Score: " + std::to_string(m_snake.GetScore()));
            m_snake.Reset();
        }
    }
}


void Game::HandleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && m_snake.GetPhysicalDirection() != Direction::Down) {
        m_snake.SetDirection(Direction::Up);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && m_snake.GetPhysicalDirection() != Direction::Up) {
        m_snake.SetDirection(Direction::Down);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && m_snake.GetPhysicalDirection() != Direction::Right) {
        m_snake.SetDirection(Direction::Left);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && m_snake.GetPhysicalDirection() != Direction::Left) {
        m_snake.SetDirection(Direction::Right);
    }
}

void Game::Render() {
    m_window.BeginDraw();
    // Render here.
    m_world.Render(*m_window.GetRenderWindow());
    m_snake.Render(*m_window.GetRenderWindow());
    if (m_textureLoaded) {
        m_window.GetRenderWindow()->draw(m_sprite);
        // Debug: Print sprite position every 60 frames (roughly once per second at 60 FPS)
        static int frameCount = 0;
        if (++frameCount % 60 == 0) {
            sf::Vector2f pos = m_sprite.getPosition();
            sf::FloatRect bounds = m_sprite.getGlobalBounds();
            std::cout << "Rendering mushroom at (" << pos.x << ", " << pos.y 
                      << ") bounds: (" << bounds.position.x << ", " << bounds.position.y 
                      << ") " << bounds.size.x << "x" << bounds.size.y << std::endl;
        }
    } else {
        static int frameCount = 0;
        if (++frameCount % 3600 == 0) { // Every 60 seconds
            std::cout << "Warning: Mushroom texture not loaded, sprite not rendered." << std::endl;
        }
    }
    m_textbox.Render(*m_window.GetRenderWindow());
    m_window.EndDraw();
}

Window* Game::GetWindow() {
    return &m_window;
}

sf::Time Game::GetElapsed() {
    return m_elapsed;
}

void Game::RestartClock() {
    m_elapsed += m_clock.restart();
}

void Game::MoveSprite(EventDetails* l_details) {
    (void)l_details; // Suppress unused parameter warning
    sf::Vector2i mousepos =
        m_window.GetEventManager()->GetMousePos(
            m_window.GetRenderWindow());
    m_sprite.setPosition(sf::Vector2f(static_cast<float>(mousepos.x), static_cast<float>(mousepos.y)));
    std::cout << "MoveSprite called! Moving sprite to: "
              << mousepos.x << ":"
              << mousepos.y << std::endl;
}

// SFML types and functions used in this file:
// - sf::Vector2u: 2D vector with unsigned int components (x, y), used for window size initialization
// - sf::Time: Time duration type, used for elapsed time tracking
//   - asSeconds(): Method to convert time to seconds (float)
// - sf::Clock: Clock object used for measuring elapsed time
//   - restart(): Method to restart the clock and return elapsed time since last restart
// - sf::seconds(): Function to create sf::Time from seconds (float)
// - sf::Keyboard: Keyboard input handling class
//   - isKeyPressed(): Method to check if a key is currently pressed
//   - Key: Enum class for keyboard keys (Up, Down, Left, Right)
