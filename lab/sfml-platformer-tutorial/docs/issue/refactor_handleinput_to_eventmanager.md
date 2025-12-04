# Refactor HandleInput to use EventManager

## Overview

Currently, `Game::HandleInput()` directly polls the keyboard using `sf::Keyboard::isKeyPressed()` for snake movement controls. This is inconsistent with the rest of the codebase, which uses the EventManager's callback system (e.g., `MoveSprite`).

## Problem

- `HandleInput()` bypasses the EventManager system
- Inconsistent input handling approach
- Harder to configure key bindings (requires code changes instead of `keys.cfg`)

## Solution

Refactor snake movement to use EventManager callbacks, similar to how `MoveSprite` is implemented.

## Comparison with network-snake

**network-snake approach (client-side input handling):**

Input handling happens entirely on the **client side**, not the server. The server only receives direction updates via UDP.

**Flow:**
1. **Graphics library** (dynamically loaded) polls input:
   - `libs/lib1/Graphics.cpp` - `checkEvents()` (raylib, uses `IsKeyPressed`)
   - `libs/lib2/Graphics.cpp` - `checkEvents()` (SFML, uses `sf::Keyboard::isKeyPressed`)
   - `libs/lib4/Graphics.cpp` - `checkEvents()` (SDL3, uses `SDL_PollEvent`)
   - All implement `IGraphics` interface from `libs/IGraphics.hpp`
   - Returns `t_event` structure with key codes

2. **Client main loop** processes events:
   - `client/src/Drawer.cpp` - `start()` method (line 71-118)
   - Calls `checkEvents()` from graphics library (line 85)
   - Routes events: `KEY` → `onKeyPress()`, `MOUSE` → `onMouseUp()`

3. **Client handles key presses:**
   - `client/src/Drawer.cpp` - `onKeyPress()` (line 239-272)
   - For direction keys (UP/DOWN/LEFT/RIGHT): calls `client->sendDirection(action)`
   - `client/src/Client.cpp` - `sendDirection()` (line 89-98)
   - Sends UDP packet to server with direction

4. **Server receives direction:**
   - `server/src/Server.cpp` - `receiveDataFromClient()` (line 184-205)
   - Receives UDP packet and calls `game->updateSnakeDirection()`
   - Server does NOT handle input, only receives direction updates

**Files involved:**
- Client: `client/src/Drawer.cpp`, `client/src/Drawer.hpp`, `client/src/Client.cpp`, `client/src/Client.hpp`
- Graphics: `libs/IGraphics.hpp`, `libs/lib1/Graphics.cpp`, `libs/lib2/Graphics.cpp`, `libs/lib4/Graphics.cpp`
- Server: `server/src/Server.cpp` (only receives, doesn't handle input)

**Current sfml project:**
- Has EventManager system with bindings from `keys.cfg`
- Uses callback registration (`AddCallback`)
- `HandleInput()` bypasses this system with direct polling

**Key difference:** network-snake uses polling with callback-style handlers on client side, while sfml project has a more sophisticated EventManager but `HandleInput()` doesn't use it.

## Potential refactor for network-snake

A possible refactor would introduce an `IEventManager` interface on the client side, with different implementations in each graphics plugin (lib1, lib2, lib4). This would:

- **Match the existing pattern:** Similar to how `IGraphics` abstracts rendering, `IEventManager` would abstract input handling
- **Plugin-specific implementations:** Each library (raylib, SFML, SDL3) would implement `IEventManager` in its own way
- **Cleaner separation:** Client wouldn't need to know about specific input polling details
- **Consistent architecture:** Input handling would follow the same abstraction pattern as graphics

**Structure:**
- `libs/IEventManager.hpp` - Interface definition
- `libs/lib1/EventManager.cpp` - raylib implementation
- `libs/lib2/EventManager.cpp` - SFML implementation  
- `libs/lib4/EventManager.cpp` - SDL3 implementation

This would move input abstraction from `checkEvents()` returning raw `t_event` to a more structured EventManager system.

**Note:** This is a **meaningful atomic change** that can be done independently:
- **Client-only:** Server doesn't need to change - it still just receives direction updates via UDP
- **Self-contained:** Only affects client input handling and graphics plugin implementations
- **No breaking changes:** The server interface remains the same (UDP direction packets)

## Todo

### Part 1: Refactor HandleInput in sfml project

- [ ] Implement `State_Game` state (part of Chapter 5 tutorial, currently commented out in `StateManager.cpp` - needed to test snake movement)
- [ ] Add snake movement bindings to `keys.cfg` (Up, Down, Left, Right arrow keys)
- [ ] Create callback methods in `Game` class: `MoveUp()`, `MoveDown()`, `MoveLeft()`, `MoveRight()`
- [ ] Register callbacks in `Game` constructor (or in `State_Game` if snake logic moves there)
- [ ] Remove direct keyboard polling from `HandleInput()`
- [ ] Test that snake movement still works correctly
- [ ] Verify direction constraints (can't move opposite direction) are maintained

### Part 2: Refactor network-snake client input handling

- [ ] Create `libs/IEventManager.hpp` interface
- [ ] Implement `EventManager` in `libs/lib1/EventManager.cpp` (raylib)
- [ ] Implement `EventManager` in `libs/lib2/EventManager.cpp` (SFML)
- [ ] Implement `EventManager` in `libs/lib4/EventManager.cpp` (SDL3)
- [ ] Update `client/src/Drawer.cpp` to use `IEventManager` instead of `checkEvents()`
- [ ] Remove `checkEvents()` from `IGraphics` interface (or deprecate it)
- [ ] Test that all three graphics libraries work correctly
- [ ] Verify server communication still works (UDP direction packets)

