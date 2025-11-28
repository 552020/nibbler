#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using MessageContainer = std::vector<std::string>;

class Textbox {
public:
    Textbox();
    Textbox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);
    ~Textbox();

    void Setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);
    void Add(std::string l_message);
    void Clear();
    void Render(sf::RenderWindow& l_wind);

private:
    MessageContainer m_messages;
    int m_numVisible;
    sf::RectangleShape m_backdrop;
    sf::Font m_font;
    sf::Text m_content;
};

// SFML types used in this file:
// - sf::Vector2f: 2D vector with float components (x, y), used for screen position
// - sf::RenderWindow: Window object used for rendering graphics, passed by reference to Render()
// - sf::RectangleShape: Rectangle shape used for rendering the backdrop (m_backdrop)
// - sf::Font: Font object used for text rendering (m_font)
// - sf::Text: Text object used for displaying messages (m_content)

