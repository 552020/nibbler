# Sprite Texture Initialization Issue

## Problem Summary
The `mushroom_2` application displays a black screen and segfaults on exit when using the `Game` class to render a sprite with a texture.

## Symptoms
- Black screen (nothing is rendered)
- Segmentation fault on application exit
- No error messages during execution

## Root Cause Analysis

### SFML 3.x API Changes (Intentional Design)
- `sf::Sprite` no longer has a default constructor (intentional change to prevent bugs)
- Sprite must be constructed with a texture: `sf::Sprite(const sf::Texture&)`
- **Key**: `sf::Texture` has a constructor that loads from file: `sf::Texture("file.png")`

### Working Code (mushroom.cpp)
The working implementation follows this sequence:
1. Create `sf::Texture` object
2. **Load texture from file**: `mushroomTexture.loadFromFile("assets/Mushroom.png")`
3. **Construct sprite with loaded texture**: `sf::Sprite mushroom(mushroomTexture)`
4. Set sprite properties (origin, position)
5. Render successfully

### Problematic Code (Game.cpp)
The current `Game` class implementation:
1. **Construct sprite in initializer list** with empty texture: `m_mushroom(m_mushroomTexture)`
2. Load texture from file in constructor body: `m_mushroomTexture.loadFromFile(...)`
3. Attempt to update sprite: `m_mushroom.setTexture(m_mushroomTexture)`

### Why This Should Work (But Doesn't)
The pattern of constructing sprite with empty texture, then loading, then calling `setTexture()` is **conceptually valid** in SFML 3.x:
- The texture object is valid from the start (just empty)
- The sprite holds a reference to the texture object
- After `loadFromFile()`, the texture's GPU data is filled
- `setTexture()` should update the sprite's view

**However**, the black screen and segfault suggest the issue is elsewhere:
- Wrong asset path (texture fails to load silently)
- Drawing before `window.clear()` / `window.display()`
- Texture going out of scope (unlikely if it's a member)
- Other unrelated bugs in the class implementation

## Technical Details

### Member Declaration Order (Game.hpp)
```cpp
Window m_window;
sf::Texture m_mushroomTexture;  // Initialized first (default constructor)
sf::Sprite m_mushroom;          // Initialized second (with empty texture)
sf::Vector2i m_increment;
```

### Current Constructor (Game.cpp)
```cpp
Game::Game() : m_window(...), m_mushroom(m_mushroomTexture) {
    // Texture is empty at this point
    m_mushroomTexture.loadFromFile("assets/Mushroom.png");  // Loaded here
    m_mushroom.setTexture(m_mushroomTexture);  // Attempted fix
}
```

## Solution: Use SFML 3.x Texture Constructor (Recommended)

SFML 3.x provides a texture constructor that loads from file, allowing full RAII initialization in the initializer list:

```cpp
// Game.cpp
Game::Game()
: m_window("Chapter 2", sf::Vector2u(800, 600))
, m_mushroomTexture("assets/Mushroom.png")  // Loads texture here
, m_mushroom(m_mushroomTexture)            // Sprite sees valid texture
{
    // Set sprite properties
    m_mushroom.setOrigin({...});
    m_mushroom.setPosition({...});
}
```

**Pros:**
- Clean, idiomatic SFML 3.x pattern
- Fully RAII (Resource Acquisition Is Initialization)
- Texture loaded before sprite construction
- No helper functions needed
- Matches SFML 3.x design intent

**Alternative (if you need error handling):**
Use `std::optional<sf::Sprite>` and construct it after loading:
```cpp
std::optional<sf::Sprite> m_mushroom;

Game::Game() : m_window(...) {
    if (m_mushroomTexture.loadFromFile("assets/Mushroom.png")) {
        m_mushroom.emplace(m_mushroomTexture);
    }
}
```

## Recommended Solution
Use the SFML 3.x texture constructor `sf::Texture("file.png")` in the initializer list. This is the idiomatic, clean way to handle texture loading in SFML 3.x.

## Status
**Open** - Awaiting implementation decision

