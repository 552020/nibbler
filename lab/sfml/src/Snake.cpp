#include "Snake.hpp"


Snake::Snake(int l_blockSize) {
    m_size = l_blockSize;
    m_bodyRect.setSize(sf::Vector2f(m_size - 1, m_size - 1));
    Reset();
}

Snake::~Snake() {
}

void Snake::Reset() {
    m_snakeBody.clear();
    m_snakeBody.push_back(SnakeSegment(5, 7));
    m_snakeBody.push_back(SnakeSegment(5, 6));
    m_snakeBody.push_back(SnakeSegment(5, 5));
    SetDirection(Direction::None); // Start off still.
    m_speed = 15;
    m_lives = 3;
    m_score = 0;
    m_lost = false;
}

void Snake::SetDirection(Direction l_dir) {
    m_dir = l_dir;
}

Direction Snake::GetDirection() {
    return m_dir;
}

int Snake::GetSpeed() {
    return m_speed;
}

sf::Vector2i Snake::GetPosition() {
    return (!m_snakeBody.empty() ? m_snakeBody.front().position : sf::Vector2i(1, 1));
}

int Snake::GetLives() {
    return m_lives;
}

int Snake::GetScore() {
    return m_score;
}

void Snake::IncreaseScore() {
    m_score += 10;
}

bool Snake::HasLost() {
    return m_lost;
}

void Snake::Lose() {
    m_lost = true;
}

void Snake::ToggleLost() {
    m_lost = !m_lost;
}

void Snake::Extend() {
    if (m_snakeBody.empty()) {
        return;
    }
    SnakeSegment& tail_head = m_snakeBody[m_snakeBody.size() - 1];
    
    if (m_snakeBody.size() > 1) {
        SnakeSegment& tail_bone = m_snakeBody[m_snakeBody.size() - 2];
        
        if (tail_head.position.x == tail_bone.position.x) {
            if (tail_head.position.y > tail_bone.position.y) {
                m_snakeBody.push_back(SnakeSegment(
                    tail_head.position.x, tail_head.position.y + 1));
            } else {
                m_snakeBody.push_back(SnakeSegment(
                    tail_head.position.x, tail_head.position.y - 1));
            }
        } else if (tail_head.position.y == tail_bone.position.y) {
            if (tail_head.position.x > tail_bone.position.x) {
                m_snakeBody.push_back(SnakeSegment(
                    tail_head.position.x + 1, tail_head.position.y));
            } else {
                m_snakeBody.push_back(SnakeSegment(
                    tail_head.position.x - 1, tail_head.position.y));
            }
        }
    } else {
        if (m_dir == Direction::Up) {
            m_snakeBody.push_back(SnakeSegment(
                tail_head.position.x, tail_head.position.y + 1));
        } else if (m_dir == Direction::Down) {
            m_snakeBody.push_back(SnakeSegment(
                tail_head.position.x, tail_head.position.y - 1));
        } else if (m_dir == Direction::Left) {
            m_snakeBody.push_back(SnakeSegment(
                tail_head.position.x + 1, tail_head.position.y));
        } else if (m_dir == Direction::Right) {
            m_snakeBody.push_back(SnakeSegment(
                tail_head.position.x - 1, tail_head.position.y));
        }
    }
}

// Cut method: Removes segments from the tail of the snake as a penalty.
// l_segments: The number of segments to remove from the tail.
// After cutting, it decreases the snake's lives by 1.
// If lives reach 0, the snake loses and the method returns early.
//
// TODO: Verify intended behavior when snake bites itself:
//   - Option 1: Lose tail from bite point to end (current implementation only removes from tail end)
//   - Option 2: Just lose a life, snake goes through itself without losing tail
//   Current implementation removes fixed number of segments from tail regardless of bite location.
void Snake::Cut(int l_segments) {
    for (int i = 0; i < l_segments; ++i) {
        m_snakeBody.pop_back();
    }
    --m_lives;
    if (!m_lives) {
        Lose();
        return;
    }
}

void Snake::Move() {
    for (int i = m_snakeBody.size() - 1; i > 0; --i) {
        m_snakeBody[i].position = m_snakeBody[i - 1].position;
    }
    
    if (m_dir == Direction::Left) {
        --m_snakeBody[0].position.x;
    } else if (m_dir == Direction::Right) {
        ++m_snakeBody[0].position.x;
    } else if (m_dir == Direction::Up) {
        --m_snakeBody[0].position.y;
    } else if (m_dir == Direction::Down) {
        ++m_snakeBody[0].position.y;
    }
}

void Snake::Tick() {
    if (m_snakeBody.empty()) {
        return;
    }
    if (m_dir == Direction::None) {
        return;
    }
    Move();
    CheckCollision();
}

void Snake::CheckCollision() {
    if (m_snakeBody.size() < 5) {
        return;
    }
    
    SnakeSegment& head = m_snakeBody.front();
    
    for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr) {
        if (itr->position == head.position) {
            int segments = m_snakeBody.end() - itr;
            Cut(segments);
            break;
        }
    }
}

void Snake::Render(sf::RenderWindow& l_window) {
    if (m_snakeBody.empty()) {
        return;
    }
    
    auto head = m_snakeBody.begin();
    m_bodyRect.setFillColor(sf::Color::Yellow);
    m_bodyRect.setPosition(sf::Vector2f(head->position.x * m_size, head->position.y * m_size));
    l_window.draw(m_bodyRect);
    
    m_bodyRect.setFillColor(sf::Color::Green);
    for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr) {
        m_bodyRect.setPosition(sf::Vector2f(itr->position.x * m_size, itr->position.y * m_size));
        l_window.draw(m_bodyRect);
    }
}

// SFML types and functions used in this file:
// - sf::Vector2f: 2D vector with float components (x, y), used for sizes and positions in pixel coordinates
// - sf::Vector2i: 2D vector with int components (x, y), used for grid positions and integer coordinates
// - sf::RenderWindow: Window object used for rendering graphics, passed by reference to Render()
//   - draw(): Method to draw drawable objects (like sf::RectangleShape) to the window
// - sf::RectangleShape: Rectangle shape used for rendering snake segments (m_bodyRect)
//   - setSize(): Method to set the size of the rectangle (used in constructor)
//   - setFillColor(): Method to set the fill color of the shape (e.g., Yellow for head, Green for body)
//   - setPosition(): Method to set the position of the shape in pixel coordinates
// - sf::Color: Color class for setting fill colors (Yellow for head, Green for body)

// Standard C++ types and functions used in this file:
// - std::vector<SnakeSegment> (SnakeContainer): Container for snake body segments (m_snakeBody)
//   - size(): Returns the number of elements in the vector
//   - empty(): Returns true if the vector is empty
//   - begin(), end(): Iterators for iterating over vector elements
//   - front(), back(): Access first/last element
//   - push_back(): Adds element to the end of the vector
//   - pop_back(): Removes element from the end of the vector
//   - clear(): Removes all elements from the vector
//   - operator[]: Access element by index
