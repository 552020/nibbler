# Segfault on Window Close

## Problem Summary
The `mushroom_2` application segfaults when closing the window (clicking the close button or when the window is destroyed).

## Symptoms
- Application runs correctly and displays the bouncing mushroom sprite
- Window closes properly (visually)
- **Segmentation fault occurs on exit** when the window is closed
- No error messages before the segfault

## Current Implementation

### Window Class
```cpp
Window::~Window() {
    Destroy();  // Calls m_window.close()
}

void Window::Destroy() {
    m_window.close();
}
```

### Game Class Member Order
```cpp
Window m_window;
sf::Texture m_mushroomTexture;
sf::Sprite m_mushroom;
sf::Vector2i m_increment;
```

### Destruction Order
Members are destroyed in **reverse declaration order**:
1. `m_increment` (destroyed first)
2. `m_mushroom` (sprite - holds pointer to texture)
3. `m_mushroomTexture` (texture)
4. `m_window` (destroyed last)

## Potential Root Causes

### 1. Sprite-Texture Lifetime Issue
- `sf::Sprite` stores a **pointer/reference** to the texture
- If the sprite is destroyed before the texture, the sprite's internal pointer becomes invalid
- However, in our case, the texture is destroyed **after** the sprite, so this should be safe
- **Status**: Likely not the issue based on destruction order

### 2. Window Destruction While Resources Active
- The window (`sf::RenderWindow`) may be trying to clean up OpenGL/rendering resources
- If the sprite or texture are still being referenced during window destruction, this could cause issues
- The window is destroyed last, so it should be safe, but there might be internal SFML state issues

### 3. SFML 3.x Internal State
- SFML 3.x may have different cleanup requirements than SFML 2.x
- The window's internal OpenGL context or rendering state might conflict with resource cleanup
- There could be a bug or undocumented requirement in SFML 3.x cleanup sequence

### 4. Event Loop Still Active
- If the event loop is still processing events while destruction happens, there might be a race condition
- The `Update()` method polls events, and if destruction happens during event processing, it could cause issues

## Investigation Needed

1. **Check SFML 3.x documentation** for proper cleanup sequence
2. **Verify destruction order** - ensure all drawable objects are destroyed before the window
3. **Test with minimal case** - create a simple test that only has window + sprite, see if segfault persists
4. **Check for double-destruction** - ensure `Destroy()` isn't being called multiple times
5. **Verify window state** - check if window needs to be explicitly closed before destruction

## Potential Solutions

### Option 1: Explicit Cleanup Order
Ensure all rendering resources are explicitly cleaned up before window destruction:
```cpp
Game::~Game() {
    // Explicitly clear sprite/texture references before window destruction
    // (though RAII should handle this)
}
```

### Option 2: Window Close Before Destruction
Explicitly close the window and wait for cleanup before destruction:
```cpp
Window::~Window() {
    if (m_window.isOpen()) {
        m_window.close();
        // Maybe need to process remaining events?
    }
}
```

### Option 3: Check SFML 3.x Requirements
Research if SFML 3.x requires specific cleanup sequence or has known issues with window destruction.

## Root Cause (Identified)

**The Actual Problem:**
The segfault is NOT about destruction order or SFML 3.x cleanup. It's a classic pattern bug:

1. User clicks close button
2. `Update()` receives `sf::Event::Closed`
3. `Update()` calls `m_window.close()` and sets `m_isDone = true`
4. **Control returns to main loop**
5. **Main loop still calls `Render()` in the same frame**
6. `Render()` tries to draw on a **closed window** → undefined behavior → segfault

**The Issue:**
```cpp
// main loop
while (!game.GetWindow()->IsDone()) {
    game.HandleInput();
    game.Update();  // Here: window.close() + m_isDone = true
    game.Render();  // <-- This still runs! Tries to draw on closed window
}
```

Drawing/displaying on a closed window causes undefined behavior and segfaults.

**Why mushroom.cpp works:**
- Uses `window.isOpen()` as loop condition
- When window closes, loop exits immediately
- No `Render()` call after window is closed

## Comparison with Working Code (mushroom.cpp)

The working `mushroom.cpp` does NOT segfault. Key differences:

**Working Pattern (mushroom.cpp):**
```cpp
while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();  // Explicitly closes window
        }
    }
    // ... render ...
}
// Window destructor handles cleanup automatically
```

**Our Pattern (mushroom_2.cpp with Game class):**
- Uses `IsDone()` flag instead of `window.isOpen()`
- Window is a member of Game class
- Window destructor is `= default` (lets RAII handle it)
- We now call `window.close()` explicitly in Update() when Closed event occurs

## What We Tried

1. **Removed `close()` from destructor** - Changed `~Window()` from calling `Destroy()` to `= default`
   - **Result**: Still segfaults

2. **Added explicit `close()` in Update()** - When Closed event occurs, call `m_window.close()` explicitly
   - **Result**: Still segfaults (current state)

3. **Kept `Destroy()` for ToggleFullscreen** - Only used for runtime window recreation
   - **Result**: No change to segfault

## Current State

- **Still segfaulting** on window close
- Working `mushroom.cpp` doesn't segfault
- Difference: `mushroom.cpp` uses `window.isOpen()` in loop condition, ours uses `IsDone()` flag
- Window is a member variable in Game class vs local variable in main()

## Solutions

### Option A: Don't call `close()` in `Update()`, only set the flag
```cpp
void Window::Update() {
    // ...
    if (event->is<sf::Event::Closed>()) {
        m_isDone = true;  // Don't call m_window.close() here
    }
}
```
Let RAII handle closing when the object is destroyed. Loop exits cleanly, no extra render after "done".

### Option B: Guard Render()
```cpp
void Game::Render() {
    if (m_window.IsDone())  // or !m_window.IsOpen()
        return;
    
    m_window.BeginDraw();
    m_window.Draw(m_mushroom);
    m_window.EndDraw();
}
```
Even if `Update()` closes the window, the same frame won't try to draw.

### Option C: Use `window.isOpen()` as the main loop condition
Match the working `mushroom.cpp` pattern:
```cpp
int main() {
    Game game;
    while (game.GetWindow()->IsOpen()) {  // Use isOpen() instead of IsDone()
        game.HandleInput();
        game.Update();
        game.Render();
    }
}
```
Then in `Update()`:
```cpp
if (event->is<sf::Event::Closed>()) {
    m_window.close();  // Fine, next loop iteration won't happen
}
```

## Solution Implemented

**Option C: Use `window.isOpen()` as the main loop condition**

1. Added `IsOpen()` method to `Window` class (wraps `m_window.isOpen()`)
2. Changed main loop from `while (!game.GetWindow()->IsDone())` to `while (game.GetWindow()->IsOpen())`
3. Removed `m_isDone = true` from `Update()` when window closes (no longer needed)

**Result:** Segfault fixed. Window closes cleanly without crashing.

## Status
**Resolved** - Fixed by using `IsOpen()` as loop condition instead of `IsDone()` flag. This prevents `Render()` from being called on a closed window.

