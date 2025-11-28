#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Window {
public:
    Window();
    Window(const std::string& l_title, const sf::Vector2u& l_size);
    ~Window();

    // Rule of Five: Copy operations deleted (sf::RenderWindow is not copyable)
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // Move operations deleted (sf::RenderWindow is not moveable in a useful way)
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

    void BeginDraw(); // Clear the window.
    void EndDraw();   // Display the changes.
    void Update();

    bool IsDone();
    bool IsOpen();
    bool IsFullscreen();
    sf::Vector2u GetWindowSize();

    void ToggleFullscreen();
    void Draw(sf::Drawable& l_drawable);
    sf::RenderWindow* GetRenderWindow();

private:
    void Setup(const std::string& l_title, const sf::Vector2u& l_size);
    void Destroy();
    void Create();

    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullscreen;
};

