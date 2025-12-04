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

    // COMMENTED OUT: HandleInput - will be moved to State_Game using EventManager
    // void HandleInput();
    void Update();
    void Render();

    Window* GetWindow();
    sf::Time GetElapsed();
    void RestartClock();
    // COMMENTED OUT: MoveSprite - will be in State_Mushroom
    // void MoveSprite(EventDetails* l_details);
    void LateUpdate();

private:
    Window m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed;
    // COMMENTED OUT: These will be moved to their respective states
    // World m_world;        // Will be in State_Game
    // Snake m_snake;        // Will be in State_Game
    // Textbox m_textbox;    // May be used in State_Game or removed
    // sf::Texture m_texture;    // Will be in State_Mushroom
    // sf::Sprite m_sprite;     // Will be in State_Mushroom
    // bool m_textureLoaded;     // Will be in State_Mushroom
    SharedContext m_context;
    StateManager m_stateManager;
};

// SFML types used in this file:
// - sf::Time: Time duration type, used for elapsed time tracking (m_elapsed) and return type of GetElapsed()
// - sf::Clock: Clock object used for measuring elapsed time (m_clock)
