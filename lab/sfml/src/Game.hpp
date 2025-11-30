#pragma once

#include "Window.hpp"
#include "World.hpp"
#include "Snake.hpp"
#include "TextBox.hpp"
#include "EventManager.hpp"
#include "StateManager.hpp"
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
    void MoveSprite(EventDetails* l_details);
    void LateUpdate();

private:
    Window m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed;
    World m_world;
    Snake m_snake;
    Textbox m_textbox;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    bool m_textureLoaded;
    SharedContext m_context;
    StateManager m_stateManager;
};

// SFML types used in this file:
// - sf::Time: Time duration type, used for elapsed time tracking (m_elapsed) and return type of GetElapsed()
// - sf::Clock: Clock object used for measuring elapsed time (m_clock)
