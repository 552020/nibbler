# Mushroom Sprite Not Visible Issue

## Problem Summary
The mushroom sprite is being rendered but has 0x0 bounds, making it invisible. The texture loads successfully (128x128), but the sprite's global bounds show size 0x0.

## Symptoms
- Texture loads successfully: "Texture loaded successfully. Mushroom sprite initialized."
- Texture size: 128x128
- Sprite positioned at (400, 300)
- **Sprite global bounds: (400, 300) size: 0x0** ← Problem
- Sprite is drawn every frame but not visible

## Root Cause Analysis

### Current Code (Game.cpp)
```cpp
Game::Game()
: m_window("Snake", sf::Vector2u(800, 600))
, m_world(sf::Vector2u(800, 600))
, m_snake(m_world.GetBlockSize())
, m_sprite(m_texture)  // ← Sprite constructed with EMPTY texture
{
    // Texture loaded HERE, but sprite already constructed
    m_textureLoaded = m_texture.loadFromFile("assets/Mushroom.png");
    if (!m_textureLoaded) {
        std::cerr << "Failed to load texture from assets/Mushroom.png" << std::endl;
    } else {
        m_sprite.setScale(sf::Vector2f(0.25f, 0.25f));
        m_sprite.setPosition(sf::Vector2f(400.0f, 300.0f));
    }
}
```

### The Problem
1. **Initialization Order Issue**: The sprite is constructed in the initializer list with `m_texture`, but at that point the texture is empty (not loaded yet).
2. **SFML 3.x Behavior**: When a sprite is constructed with an empty texture, it gets 0x0 bounds. Even after loading the texture later, the sprite's bounds remain 0x0 because the sprite was already initialized with the empty texture's size.
3. **setTexture() Not Called**: We're not calling `setTexture()` after loading, which might be needed to update the sprite's internal state.

### Why This Happens
In SFML 3.x, `sf::Sprite` must be constructed with a valid (loaded) texture. The sprite stores the texture size at construction time. If the texture is empty, the sprite has 0x0 bounds and won't render, even if the texture is loaded later.

## Solutions

### Solution 1: Use Texture Constructor That Loads From File (Recommended)
```cpp
Game::Game()
: m_window("Snake", sf::Vector2u(800, 600))
, m_world(sf::Vector2u(800, 600))
, m_snake(m_world.GetBlockSize())
, m_texture("assets/Mushroom.png")  // ← Loads texture in initializer list
, m_sprite(m_texture)                // ← Sprite sees loaded texture
{
    m_textbox.Setup(5, 14, 350, sf::Vector2f(225, 0));
    m_textbox.Add("Seeded random number generator with: " + std::to_string(time(NULL)));
    
    m_textureLoaded = true;  // Texture constructor throws on failure, so if we get here it's loaded
    m_sprite.setScale(sf::Vector2f(0.25f, 0.25f));
    m_sprite.setPosition(sf::Vector2f(400.0f, 300.0f));
}
```

**Pros:**
- Clean RAII pattern
- Texture loaded before sprite construction
- Sprite gets correct bounds immediately

**Cons:**
- Throws exception if texture file not found (need try-catch or ensure file exists)

### Solution 2: Load Texture First, Then Construct Sprite
```cpp
Game::Game()
: m_window("Snake", sf::Vector2u(800, 600))
, m_world(sf::Vector2u(800, 600))
, m_snake(m_world.GetBlockSize())
// Don't initialize m_sprite in initializer list
{
    m_textbox.Setup(5, 14, 350, sf::Vector2f(225, 0));
    m_textbox.Add("Seeded random number generator with: " + std::to_string(time(NULL)));
    
    // Load texture first
    m_textureLoaded = m_texture.loadFromFile("assets/Mushroom.png");
    if (m_textureLoaded) {
        // Now construct sprite with loaded texture
        m_sprite = sf::Sprite(m_texture);  // Copy assignment or move
        m_sprite.setScale(sf::Vector2f(0.25f, 0.25f));
        m_sprite.setPosition(sf::Vector2f(400.0f, 300.0f));
    }
}
```

**Note**: This might not work if `sf::Sprite` doesn't have a default constructor in SFML 3.x. Need to check.

### Solution 3: Use setTexture() After Loading
```cpp
Game::Game()
: m_window("Snake", sf::Vector2u(800, 600))
, m_world(sf::Vector2u(800, 600))
, m_snake(m_world.GetBlockSize())
, m_sprite(m_texture)  // Construct with empty texture
{
    m_textbox.Setup(5, 14, 350, sf::Vector2f(225, 0));
    m_textbox.Add("Seeded random number generator with: " + std::to_string(time(NULL)));
    
    m_textureLoaded = m_texture.loadFromFile("assets/Mushroom.png");
    if (m_textureLoaded) {
        m_sprite.setTexture(m_texture, true);  // ← Reset texture rect
        m_sprite.setScale(sf::Vector2f(0.25f, 0.25f));
        m_sprite.setPosition(sf::Vector2f(400.0f, 300.0f));
    }
}
```

**Note**: Need to verify if `setTexture()` with `resetRect=true` updates the bounds correctly.

## Recommended Solution
Use **Solution 1** (Texture constructor that loads from file) as it's the cleanest and most idiomatic SFML 3.x pattern. Wrap in try-catch if error handling is needed, or ensure the texture file exists.

## Status
**Open** - Awaiting implementation

