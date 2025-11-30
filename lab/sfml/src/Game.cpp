#include "Game.hpp"
#include <ctime>
#include <string>
#include <iostream>
#include <cerrno>

Game::Game()
: m_window("Chapter 5", sf::Vector2u(800, 600))
, m_world(sf::Vector2u(800, 600))
, m_snake(m_world.GetBlockSize())
, m_sprite(m_texture)
, m_stateManager(&m_context)
{
    // Initialize shared context
    m_context.m_wind = &m_window;
    m_context.m_eventManager = m_window.GetEventManager();
    
    // Start with intro state
    m_stateManager.SwitchTo(StateType::Intro);
    
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
    
    // Global callback (StateType(0)) - active regardless of current state
    m_window.GetEventManager()->AddCallback(StateType(0), "Move",
                                            &Game::MoveSprite, this);
}

Game::~Game() {
}

void Game::Update() {
    m_window.Update();
    // NOTE: Tutorial bug - tutorial shows m_stateManager.Update(m_elapsed) but m_elapsed
    // is accumulated time (keeps growing), not delta time. We need time since last restart.
    // Use restart() to get delta time for this frame AND reset clock for next frame
    sf::Time deltaTime = m_clock.restart();
    m_stateManager.Update(deltaTime);
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
    m_stateManager.Draw();
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

void Game::LateUpdate() {
    m_stateManager.ProcessRequests();
    // Clock is now restarted in Update(), so we don't need to restart here
    // RestartClock(); // Commented out - clock restarted in Update() now
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
