#include "Window.hpp"

Window::Window() {
    Setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string& l_title, const sf::Vector2u& l_size) {
    Setup(l_title, l_size);
}

// SFML 3.x: sf::RenderWindow destructor handles all cleanup automatically (RAII)
// Calling close() in destructor is redundant and can cause segfaults
// Destroy() is only used for explicit runtime cleanup (e.g., ToggleFullscreen)
Window::~Window() = default;

void Window::Setup(const std::string& l_title, const sf::Vector2u& l_size) {
    m_windowTitle = l_title;
    m_windowSize = l_size;
    m_isFullscreen = false;
    m_isDone = false;
    Create();
}

// SFML 3.x change: Fullscreen is now handled via State enum, not Style enum
// In SFML 2.x: sf::Style::Fullscreen was a style flag
// In SFML 3.x: sf::State::Fullscreen is a separate state parameter
// Also: sf::Uint32 was removed in SFML 3.x, use std::uint32_t instead
void Window::Create() {
    sf::VideoMode mode = m_isFullscreen ? sf::VideoMode::getDesktopMode() 
                                        : sf::VideoMode({m_windowSize.x, m_windowSize.y});
    std::uint32_t style = sf::Style::Default;  // Changed from sf::Uint32 to std::uint32_t in SFML 3.x
    sf::State state = m_isFullscreen ? sf::State::Fullscreen : sf::State::Windowed;
    
    m_window.create(mode, m_windowTitle, style, state);
}

void Window::Destroy() {
    m_window.close();
}

void Window::Update() {
    // std::optional: C++17 feature that represents a value that may or may not exist
    // pollEvent() returns std::optional<Event> - if there's an event, it contains it; if not, it's empty
    // The event object comes from m_window.pollEvent() which retrieves the next event from the window's event queue
    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();  // Close window - loop will exit on next iteration since IsOpen() will return false
        } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::F5) {
                ToggleFullscreen();
            }
        }
    }
}

void Window::ToggleFullscreen() {
    m_isFullscreen = !m_isFullscreen;
    Destroy();
    Create();
}

void Window::BeginDraw() {
    m_window.clear(sf::Color::Black);
}

void Window::EndDraw() {
    m_window.display();
}

bool Window::IsDone() {
    return m_isDone;
}

bool Window::IsOpen() {
    return m_window.isOpen();
}

bool Window::IsFullscreen() {
    return m_isFullscreen;
}

sf::Vector2u Window::GetWindowSize() {
    return m_windowSize;
}

void Window::Draw(sf::Drawable& l_drawable) {
    m_window.draw(l_drawable);
}

sf::RenderWindow* Window::GetRenderWindow() {
    return &m_window;
}
