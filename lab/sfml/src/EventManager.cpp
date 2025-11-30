#include "EventManager.hpp"
#include "StateManager.hpp"  // For StateType definition
#include <fstream>
#include <sstream>
#include <iostream>

EventManager::EventManager() : m_hasFocus(true), m_currentState(StateType::Mushroom) {
    LoadBindings();
}

EventManager::~EventManager() {
    for (auto& itr : m_bindings) {
        delete itr.second;
        itr.second = nullptr;
    }
}

bool EventManager::AddBinding(Binding* l_binding) {
    if (m_bindings.find(l_binding->m_name) != m_bindings.end()) {
        return false;
    }
    return m_bindings.emplace(l_binding->m_name, l_binding).second;
}

bool EventManager::RemoveBinding(std::string l_name) {
    auto itr = m_bindings.find(l_name);
    if (itr == m_bindings.end()) {
        return false;
    }
    delete itr->second;
    m_bindings.erase(itr);
    return true;
}

void EventManager::SetFocus(const bool& l_focus) {
    m_hasFocus = l_focus;
}

void EventManager::SetCurrentState(StateType l_state) {
    m_currentState = l_state;
}

/// @brief Handles incoming SFML events and matches them to registered bindings.
/// 
/// This method processes SFML events by iterating through all registered bindings
/// and their associated events. When a match is found:
/// - For keyboard events (KeyDown/KeyUp): Checks if the key code matches the binding's event code
/// - For mouse button events (MButtonDown/MButtonUp): Checks if the button matches and stores mouse position
/// - For MouseWheel events: Stores the wheel delta value
/// - For WindowResized events: Stores the new window dimensions (width, height)
/// - For TextEntered events: Stores the unicode character entered
/// 
/// When a match is found, the binding's event count is incremented and relevant
/// event details are stored in the binding's EventDetails structure.
/// 
/// @param l_event Reference to the SFML event to process
void EventManager::HandleEvent(sf::Event& l_event) {
    // Handling SFML events.
    EventType sfmlEvent = EventType::Closed;
    
    // Map SFML 3.x variant-based events to EventType
    if (l_event.is<sf::Event::Closed>()) {
        sfmlEvent = EventType::Closed;
    } else if (l_event.is<sf::Event::Resized>()) {
        sfmlEvent = EventType::WindowResized;
    } else if (l_event.is<sf::Event::FocusLost>()) {
        sfmlEvent = EventType::LostFocus;
    } else if (l_event.is<sf::Event::FocusGained>()) {
        sfmlEvent = EventType::GainedFocus;
    } else if (l_event.is<sf::Event::TextEntered>()) {
        sfmlEvent = EventType::TextEntered;
    } else if (l_event.is<sf::Event::KeyPressed>()) {
        sfmlEvent = EventType::KeyDown;
    } else if (l_event.is<sf::Event::KeyReleased>()) {
        sfmlEvent = EventType::KeyUp;
    } else if (l_event.is<sf::Event::MouseWheelScrolled>()) {
        sfmlEvent = EventType::MouseWheel;
    } else if (l_event.is<sf::Event::MouseButtonPressed>()) {
        sfmlEvent = EventType::MButtonDown;
    } else if (l_event.is<sf::Event::MouseButtonReleased>()) {
        sfmlEvent = EventType::MButtonUp;
    } else if (l_event.is<sf::Event::MouseEntered>()) {
        sfmlEvent = EventType::MouseEntered;
    } else if (l_event.is<sf::Event::MouseLeft>()) {
        sfmlEvent = EventType::MouseLeft;
    } else {
        return; // Unknown event type
    }
    
    for (auto& b_itr : m_bindings) {
        Binding* bind = b_itr.second;
        for (auto& e_itr : bind->m_events) {
            if (e_itr.first != sfmlEvent) {
                continue;
            }
            if (sfmlEvent == EventType::KeyDown ||
                sfmlEvent == EventType::KeyUp) {
                if (const auto* keyEvent = l_event.getIf<sf::Event::KeyPressed>()) {
                    if (e_itr.second.m_code == static_cast<int>(keyEvent->code)) {
                        if (bind->m_details.m_keyCode != -1) {
                            bind->m_details.m_keyCode = static_cast<int>(keyEvent->code);
                        }
                        ++(bind->c);
                        break;
                    }
                } else if (const auto* keyEvent = l_event.getIf<sf::Event::KeyReleased>()) {
                    if (e_itr.second.m_code == static_cast<int>(keyEvent->code)) {
                        if (bind->m_details.m_keyCode != -1) {
                            bind->m_details.m_keyCode = static_cast<int>(keyEvent->code);
                        }
                        ++(bind->c);
                        break;
                    }
                }
            } else if (sfmlEvent == EventType::MButtonDown ||
                       sfmlEvent == EventType::MButtonUp) {
                if (const auto* mouseEvent = l_event.getIf<sf::Event::MouseButtonPressed>()) {
                    std::cout << "Mouse button pressed: button=" << static_cast<int>(mouseEvent->button) 
                              << " at (" << mouseEvent->position.x << ", " << mouseEvent->position.y << ")" << std::endl;
                    if (e_itr.second.m_code == static_cast<int>(mouseEvent->button)) {
                        bind->m_details.m_mouse.x = mouseEvent->position.x;
                        bind->m_details.m_mouse.y = mouseEvent->position.y;
                        if (bind->m_details.m_keyCode != -1) {
                            bind->m_details.m_keyCode = static_cast<int>(mouseEvent->button);
                        }
                        ++(bind->c);
                        break;
                    }
                } else if (const auto* mouseEvent = l_event.getIf<sf::Event::MouseButtonReleased>()) {
                    std::cout << "Mouse button released: button=" << static_cast<int>(mouseEvent->button) 
                              << " at (" << mouseEvent->position.x << ", " << mouseEvent->position.y << ")" << std::endl;
                    if (e_itr.second.m_code == static_cast<int>(mouseEvent->button)) {
                        bind->m_details.m_mouse.x = mouseEvent->position.x;
                        bind->m_details.m_mouse.y = mouseEvent->position.y;
                        if (bind->m_details.m_keyCode != -1) {
                            bind->m_details.m_keyCode = static_cast<int>(mouseEvent->button);
                        }
                        ++(bind->c);
                        break;
                    }
                }
            } else {
                // No need for additional checking.
                if (sfmlEvent == EventType::MouseWheel) {
                    if (const auto* wheelEvent = l_event.getIf<sf::Event::MouseWheelScrolled>()) {
                        bind->m_details.m_mouseWheelDelta = static_cast<int>(wheelEvent->delta);
                    }
                } else if (sfmlEvent == EventType::WindowResized) {
                    if (const auto* resizeEvent = l_event.getIf<sf::Event::Resized>()) {
                        bind->m_details.m_size.x = static_cast<int>(resizeEvent->size.x);
                        bind->m_details.m_size.y = static_cast<int>(resizeEvent->size.y);
                    }
                } else if (sfmlEvent == EventType::TextEntered) {
                    if (const auto* textEvent = l_event.getIf<sf::Event::TextEntered>()) {
                        bind->m_details.m_textEntered = textEvent->unicode;
                    }
                }
                ++(bind->c);
            }
        }
    }
}

void EventManager::Update() {
    if (!m_hasFocus) {
        return;
    }
    for (auto& b_itr : m_bindings) {
        Binding* bind = b_itr.second;
        for (auto& e_itr : bind->m_events) {
            switch (e_itr.first) {
                case(EventType::Keyboard):
                    if (sf::Keyboard::isKeyPressed(
                        sf::Keyboard::Key(e_itr.second.m_code))) {
                        std::cout << "Keyboard key " << e_itr.second.m_code << " is currently pressed (continuous check)" << std::endl;
                        if (bind->m_details.m_keyCode != -1) {
                            bind->m_details.m_keyCode = e_itr.second.m_code;
                        }
                        ++(bind->c);
                    }
                    break;
                case(EventType::Mouse):
                    if (sf::Mouse::isButtonPressed(
                        sf::Mouse::Button(e_itr.second.m_code))) {
                        // std::cout << "Mouse button " << e_itr.second.m_code << " is currently pressed (continuous check)" << std::endl;
                        if (bind->m_details.m_keyCode != -1) {
                            bind->m_details.m_keyCode = e_itr.second.m_code;
                        }
                        ++(bind->c);
                    }
                    break;
                case(EventType::Joystick):
                    // Up for expansion.
                    break;
                default:
                    // Other event types are handled in HandleEvent, not here
                    break;
            }
        }
        if (static_cast<int>(bind->m_events.size()) == bind->c) {
            std::cout << "Binding '" << bind->m_name << "' triggered! All " << bind->c << " events matched." << std::endl;
            
            // Check callbacks for current state
            auto stateCallbacks = m_callbacks.find(m_currentState);
            if (stateCallbacks != m_callbacks.end()) {
                auto callItr = stateCallbacks->second.find(bind->m_name);
                if (callItr != stateCallbacks->second.end()) {
                    callItr->second(&bind->m_details);
                }
            }
            
            // Check global callbacks (StateType(0) - always active regardless of state)
            auto otherCallbacks = m_callbacks.find(StateType(0));
            if (otherCallbacks != m_callbacks.end()) {
                auto callItr = otherCallbacks->second.find(bind->m_name);
                if (callItr != otherCallbacks->second.end()) {
                    callItr->second(&bind->m_details);
                }
            }
        }
        bind->c = 0;
        bind->m_details.Clear();
    }
}

void EventManager::LoadBindings() {
    std::string delimiter = ":";
    std::ifstream bindings;
    bindings.open("keys.cfg");
    if (!bindings.is_open()) {
        std::cout << "! Failed loading keys.cfg." << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(bindings, line)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream keystream(line);
        std::string callbackName;
        keystream >> callbackName;
        if (callbackName.empty()) {
            continue;
        }
        Binding* bind = new Binding(callbackName);
        
        while (!keystream.eof()) {
            std::string keyval;
            keystream >> keyval;
            if (keyval.empty()) {
                break;
            }
            int start = 0;
            std::string::size_type end = keyval.find(delimiter);
            if (end == std::string::npos) {
                delete bind;
                bind = nullptr;
                break;
            }
            try {
                EventType type = EventType(
                    stoi(keyval.substr(start, end - start)));
                std::string codeStr = keyval.substr(end + delimiter.length());
                std::string::size_type nextDelim = codeStr.find(delimiter);
                int code = stoi(nextDelim == std::string::npos ? codeStr : codeStr.substr(0, nextDelim));
                EventInfo eventInfo;
                eventInfo.m_code = code;
                bind->BindEvent(type, eventInfo);
            } catch (...) {
                delete bind;
                bind = nullptr;
                break;
            }
        }
        
        if (bind && !AddBinding(bind)) {
            delete bind;
        }
    }
    bindings.close();
}

