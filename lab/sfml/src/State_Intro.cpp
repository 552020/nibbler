#include "State_Intro.hpp"
#include "StateManager.hpp"
#include "Window.hpp"
#include <iostream>

State_Intro::State_Intro(StateManager* l_stateManager)
    : BaseState(l_stateManager), m_introSprite(m_introTexture), m_text(m_font), m_timePassed(0.0f) {
}

State_Intro::~State_Intro() {
}

void State_Intro::OnCreate() {
    m_timePassed = 0.0f;
    sf::Vector2u windowSize = m_stateMgr->GetContext()->
        m_wind->GetRenderWindow()->getSize();

    if (!m_introTexture.loadFromFile("assets/intro.png")) {
        std::cerr << "Error: Failed to load texture from assets/intro.png" << std::endl;
    } else {
        std::cout << "Intro texture loaded successfully. Size: " 
                  << m_introTexture.getSize().x << "x" << m_introTexture.getSize().y << std::endl;
        // Set texture with resetRect=true to update sprite bounds after loading
        m_introSprite.setTexture(m_introTexture, true);
        sf::Vector2u textureSize = m_introTexture.getSize();
        m_introSprite.setOrigin(sf::Vector2f(textureSize.x / 2.0f,
            textureSize.y / 2.0f));
        m_introSprite.setPosition(sf::Vector2f(windowSize.x / 2.0f, 0));
        std::cout << "Intro sprite positioned at (" << windowSize.x / 2.0f << ", 0)" << std::endl;
        std::cout << "Texture size: " << textureSize.x << "x" << textureSize.y << std::endl;
        // Verify sprite bounds
        sf::FloatRect bounds = m_introSprite.getGlobalBounds();
        std::cout << "Sprite global bounds: (" << bounds.position.x << ", " << bounds.position.y 
                  << ") size: " << bounds.size.x << "x" << bounds.size.y << std::endl;
    }

    if (!m_font.openFromFile("assets/arial/ARIAL.TTF")) {
        std::cerr << "Error: Failed to load font from assets/arial/ARIAL.TTF" << std::endl;
    }
    m_text.setFont(m_font);
    m_text.setString({ "Press SPACE to continue" });
    m_text.setCharacterSize(15);
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.0f,
        textRect.position.y + textRect.size.y / 2.0f));
    m_text.setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));

    EventManager* evMgr = m_stateMgr->
        GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::Intro, "Intro_Continue",
        &State_Intro::Continue, this);
}

void State_Intro::OnDestroy() {
    EventManager* evMgr = m_stateMgr->
        GetContext()->m_eventManager;
    evMgr->RemoveCallback(StateType::Intro, "Intro_Continue");
}

void State_Intro::Activate() {
}

void State_Intro::Deactivate() {
}

void State_Intro::Update(const sf::Time& l_time) {
    if (m_timePassed < 5.0f) { // Less than five seconds.
        m_timePassed += l_time.asSeconds();
        sf::Vector2f currentPos = m_introSprite.getPosition();
        m_introSprite.setPosition(sf::Vector2f(currentPos.x,
            currentPos.y + (48 * l_time.asSeconds())));
    }
}

void State_Intro::Draw() {
    sf::RenderWindow* window = m_stateMgr->
        GetContext()->m_wind->GetRenderWindow();
    window->draw(m_introSprite);
    if (m_timePassed >= 5.0f) {
        window->draw(m_text);
    }
}

void State_Intro::Continue(EventDetails* l_details) {
    (void)l_details; // Suppress unused parameter warning
    if (m_timePassed >= 5.0f) {
        m_stateMgr->SwitchTo(StateType::MainMenu);
        m_stateMgr->Remove(StateType::Intro);
    }
}

// SFML types and functions used in this file:
// - sf::Texture::loadFromFile(): Loads texture from file
// - sf::Texture::getSize(): Gets texture dimensions
// - sf::Sprite::setTexture(): Sets the texture for the sprite
// - sf::Sprite::setOrigin(): Sets the origin point of the sprite
// - sf::Sprite::setPosition(): Sets the position of the sprite
// - sf::Sprite::getPosition(): Gets the current position of the sprite
// - sf::Font::openFromFile(): Loads font from file
// - sf::Text::setFont(): Sets the font for the text
// - sf::Text::setString(): Sets the text string
// - sf::Text::setCharacterSize(): Sets the character size
// - sf::Text::getLocalBounds(): Gets the local bounding rectangle
// - sf::Text::setOrigin(): Sets the origin point of the text
// - sf::Text::setPosition(): Sets the position of the text
// - sf::Time::asSeconds(): Converts time to seconds (float)
// - sf::Vector2u: 2D vector with unsigned integer components
// - sf::FloatRect: Rectangle with float components
// - sf::RenderWindow::draw(): Draws a drawable object
// - sf::RenderWindow::getSize(): Gets the window size

