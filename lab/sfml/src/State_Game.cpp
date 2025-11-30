#include "State_Game.hpp"
#include "StateManager.hpp"
#include "Window.hpp"
#include <ctime>
#include <iostream>

State_Game::State_Game(StateManager* l_stateManager)
    : BaseState(l_stateManager)
    , m_world(sf::Vector2u(800, 600))
    , m_snake(m_world.GetBlockSize())
    , m_textbox()  // Must be in initializer list to match declaration order
    , m_isDying(false)
    , m_deathAnimationTime(0.0f) {
    // World is initialized with default size (800, 600)
    // Window size will be updated in OnCreate() if needed
}

State_Game::~State_Game() {
}

void State_Game::OnCreate() {
    // Seed random number generator for apple placement
    srand(time(nullptr));
    
    // Get window size (World is already initialized in constructor with default size)
    // Note: World constructor takes window size, so it's set during member initialization
    // If window size differs from 800x600, we'd need to recreate World here
    // For now, assuming window is 800x600 as per Game constructor
    
    // Reset snake to starting position
    m_snake.Reset();
    
    // Setup textbox
    m_textbox.Setup(5, 14, 350, sf::Vector2f(225, 0));
    m_textbox.Add("Snake game started!");
    
    // Register input callbacks
    EventManager* evMgr = m_stateMgr->
        GetContext()->m_eventManager;
    // Arrow keys
    evMgr->AddCallback(StateType::Game, "Key_Up",
        &State_Game::MoveUp, this);
    evMgr->AddCallback(StateType::Game, "Key_Down",
        &State_Game::MoveDown, this);
    evMgr->AddCallback(StateType::Game, "Key_Left",
        &State_Game::MoveLeft, this);
    evMgr->AddCallback(StateType::Game, "Key_Right",
        &State_Game::MoveRight, this);
    // WASD keys (same callbacks as arrow keys)
    evMgr->AddCallback(StateType::Game, "Key_W",
        &State_Game::MoveUp, this);
    evMgr->AddCallback(StateType::Game, "Key_S",
        &State_Game::MoveDown, this);
    evMgr->AddCallback(StateType::Game, "Key_A",
        &State_Game::MoveLeft, this);
    evMgr->AddCallback(StateType::Game, "Key_D",
        &State_Game::MoveRight, this);
    // Other controls
    evMgr->AddCallback(StateType::Game, "Key_P",
        &State_Game::Pause, this);
    evMgr->AddCallback(StateType::Game, "Key_Escape",
        &State_Game::MainMenu, this);
}

void State_Game::OnDestroy() {
    EventManager* evMgr = m_stateMgr->
        GetContext()->m_eventManager;
    // Arrow keys
    evMgr->RemoveCallback(StateType::Game, "Key_Up");
    evMgr->RemoveCallback(StateType::Game, "Key_Down");
    evMgr->RemoveCallback(StateType::Game, "Key_Left");
    evMgr->RemoveCallback(StateType::Game, "Key_Right");
    // WASD keys
    evMgr->RemoveCallback(StateType::Game, "Key_W");
    evMgr->RemoveCallback(StateType::Game, "Key_S");
    evMgr->RemoveCallback(StateType::Game, "Key_A");
    evMgr->RemoveCallback(StateType::Game, "Key_D");
    // Other controls
    evMgr->RemoveCallback(StateType::Game, "Key_P");
    evMgr->RemoveCallback(StateType::Game, "Key_Escape");
}

void State_Game::Activate() {
}

void State_Game::Deactivate() {
}

void State_Game::Update(const sf::Time& l_time) {
    // Update death animation timer
    if (m_isDying) {
        m_deathAnimationTime -= l_time.asSeconds();
        if (m_deathAnimationTime <= 0.0f) {
            // Animation finished, switch to game over
            std::cout << "Death animation finished. Switching to GameOver state..." << std::endl;
            // m_stateMgr->SwitchTo(StateType::GameOver); // Commented out until State_GameOver is created
            std::cout << "WARNING: State_GameOver not implemented yet!" << std::endl;
        }
    }
    
    // Accumulate elapsed time for snake movement timing
    static float elapsed = 0.0f;
    elapsed += l_time.asSeconds();
    
    // Snake moves based on speed (default speed is 15, meaning 15 moves per second)
    // So we need to move every 1/15 seconds = 0.0667 seconds
    float moveInterval = 1.0f / static_cast<float>(m_snake.GetSpeed());
    
    if (elapsed >= moveInterval) {
        elapsed -= moveInterval;
        
        // Check if snake would hit wall before moving
        if (!m_snake.HasLost()) {
            sf::Vector2i currentPos = m_snake.GetPosition();
            Direction currentDir = m_snake.GetDirection();
            
            if (m_world.WouldHitWall(currentPos, currentDir)) {
                std::cout << "Preventing move: Snake would hit wall at (" 
                          << currentPos.x << ", " << currentPos.y 
                          << ") moving " << static_cast<int>(currentDir) << std::endl;
                m_snake.Lose(); // Stop the snake
                m_isDying = true; // Start death animation
                m_deathAnimationTime = 2.0f; // 2 seconds of blinking
            } else {
                // Update snake (movement and collision detection)
                m_snake.Tick();
                
                // Update world (check for apple eaten, wall collision)
                m_world.Update(m_snake, m_textbox);
            }
        } else {
            // Snake has lost, don't move
            // But still update world for apple checks (though snake won't move)
        }
        
        // Debug: Check snake state
        static int moveCount = 0;
        std::cout << "Move " << moveCount << ": Snake position: (" 
                  << m_snake.GetPosition().x << ", " << m_snake.GetPosition().y 
                  << "), Lost: " << m_snake.HasLost() 
                  << ", Body size: " << m_snake.GetPosition().x << std::endl;
        moveCount++;
        
        // Check for game over conditions
        if (m_snake.HasLost()) {
            std::cout << "Game Over! Snake has lost. Attempting to switch to GameOver state..." << std::endl;
            // Switch to game over state
            // NOTE: State_GameOver doesn't exist yet, so this will fail silently
            // For now, just pause or show message
            std::cout << "WARNING: State_GameOver not implemented yet!" << std::endl;
            // m_stateMgr->SwitchTo(StateType::GameOver); // Commented out until State_GameOver is created
        }
    }
}

void State_Game::Draw() {
    sf::RenderWindow* window = m_stateMgr->
        GetContext()->m_wind->GetRenderWindow();
    
    // Draw world (walls and apple)
    m_world.Render(*window);
    
    // Draw snake with blinking effect if dying
    if (m_isDying) {
        // Blink effect: invert colors every 0.1 seconds (10 times per second)
        // Use modulo to create blinking effect
        int blinkPhase = static_cast<int>(m_deathAnimationTime * 10.0f) % 2;
        bool invertColors = (blinkPhase == 1);
        m_snake.Render(*window, invertColors);
    } else {
        m_snake.Render(*window);
    }
    
    // Draw textbox
    m_textbox.Render(*window);
}

void State_Game::MoveUp(EventDetails* l_details) {
    (void)l_details; // Suppress unused parameter warning
    std::cout << "MoveUp called! Current direction: " << static_cast<int>(m_snake.GetPhysicalDirection()) 
              << ", Body size: " << m_snake.GetPosition().x << "," << m_snake.GetPosition().y << std::endl;
    if (m_snake.GetPhysicalDirection() != Direction::Down) {
        m_snake.SetDirection(Direction::Up);
    }
}

void State_Game::MoveDown(EventDetails* l_details) {
    (void)l_details; // Suppress unused parameter warning
    if (m_snake.GetPhysicalDirection() != Direction::Up) {
        m_snake.SetDirection(Direction::Down);
    }
}

void State_Game::MoveLeft(EventDetails* l_details) {
    (void)l_details; // Suppress unused parameter warning
    if (m_snake.GetPhysicalDirection() != Direction::Right) {
        m_snake.SetDirection(Direction::Left);
    }
}

void State_Game::MoveRight(EventDetails* l_details) {
    (void)l_details; // Suppress unused parameter warning
    if (m_snake.GetPhysicalDirection() != Direction::Left) {
        m_snake.SetDirection(Direction::Right);
    }
}

void State_Game::Pause(EventDetails* l_details) {
    (void)l_details; // Suppress unused parameter warning
    m_stateMgr->SwitchTo(StateType::Paused);
}

void State_Game::MainMenu(EventDetails* l_details) {
    (void)l_details; // Suppress unused parameter warning
    m_stateMgr->SwitchTo(StateType::MainMenu);
}
