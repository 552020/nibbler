#include "Game.hpp"

Game::Game()
: m_window("Snake", sf::Vector2u(800, 600))
, m_world(sf::Vector2u(800, 600))
, m_snake(m_world.GetBlockSize())
{
}

Game::~Game() {
}

void Game::Update() {
    m_window.Update(); // Update window events.
    
    float timestep = 1.0f / m_snake.GetSpeed();
    if (m_elapsed.asSeconds() >= timestep) {
        m_snake.Tick();
        m_world.Update(m_snake);
        m_elapsed -= sf::seconds(timestep);
        
        if (m_snake.HasLost()) {
            m_snake.Reset();
        }
    }
}


void Game::HandleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && m_snake.GetDirection() != Direction::Down) {
        m_snake.SetDirection(Direction::Up);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && m_snake.GetDirection() != Direction::Up) {
        m_snake.SetDirection(Direction::Down);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && m_snake.GetDirection() != Direction::Right) {
        m_snake.SetDirection(Direction::Left);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && m_snake.GetDirection() != Direction::Left) {
        m_snake.SetDirection(Direction::Right);
    }
}

void Game::Render() {
    m_window.BeginDraw();
    // Render here.
    m_world.Render(*m_window.GetRenderWindow());
    m_snake.Render(*m_window.GetRenderWindow());
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

