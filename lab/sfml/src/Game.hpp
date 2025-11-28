#pragma once

#include "Window.hpp"
#include "World.hpp"
#include "Snake.hpp"
#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    ~Game();

    // Rule of Five: Copy operations deleted (Window is not copyable)
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    // Move operations deleted (Window is not moveable)
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

    void HandleInput();
    void Update();
    void Render();

    Window* GetWindow();
    sf::Time GetElapsed();
    void RestartClock();

private:
    Window m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed;
    World m_world;
    Snake m_snake;
};

