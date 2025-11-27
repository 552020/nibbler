#pragma once

#include "Window.hpp"
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

private:
    void MoveMushroom();

    Window m_window;
    sf::Texture m_mushroomTexture;
    sf::Sprite m_mushroom;
    sf::Vector2i m_increment;
};

