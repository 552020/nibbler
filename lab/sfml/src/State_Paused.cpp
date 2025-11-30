#include "State_Paused.hpp"
#include "StateManager.hpp"
#include "Window.hpp"
#include <iostream>

State_Paused::State_Paused(StateManager* l_stateManager)
    : BaseState(l_stateManager), m_text(m_font) {
}

State_Paused::~State_Paused() {
}

void State_Paused::OnCreate() {
    SetTransparent(true); // Set our transparency flag.
    if (!m_font.openFromFile("assets/arial/ARIAL.TTF")) {
        std::cerr << "Error: Failed to load font from assets/arial/ARIAL.TTF" << std::endl;
    }
    m_text.setFont(m_font);
    m_text.setString(sf::String("PAUSED"));
    m_text.setCharacterSize(14);
    m_text.setStyle(sf::Text::Bold);
    sf::Vector2u windowSize = m_stateMgr->
        GetContext()->m_wind->GetRenderWindow()->getSize();
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.0f,
        textRect.position.y + textRect.size.y / 2.0f));
    m_text.setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));
    m_rect.setSize(sf::Vector2f(windowSize));
    m_rect.setPosition(sf::Vector2f(0, 0));
    m_rect.setFillColor(sf::Color(0, 0, 0, 150));
    EventManager* evMgr = m_stateMgr->
        GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::Paused, "Key_P",
        &State_Paused::Unpause, this);
}

void State_Paused::OnDestroy() {
    EventManager* evMgr = m_stateMgr->
        GetContext()->m_eventManager;
    evMgr->RemoveCallback(StateType::Paused, "Key_P");
}

void State_Paused::Activate() {
}

void State_Paused::Deactivate() {
}

void State_Paused::Update(const sf::Time& l_time) {
    (void)l_time; // Suppress unused parameter warning
}

void State_Paused::Draw() {
    sf::RenderWindow* wind = m_stateMgr->
        GetContext()->m_wind->GetRenderWindow();
    wind->draw(m_rect);
    wind->draw(m_text);
}

void State_Paused::Unpause(EventDetails* l_details) {
    (void)l_details; // Suppress unused parameter warning
    m_stateMgr->SwitchTo(StateType::Game);
}

