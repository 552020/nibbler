# Finish Snake Game - Integration with State System

## Overview

The tutorial moves on to a different game after Chapter 5, leaving our snake game incomplete. We need to integrate the existing snake game logic with the new state system so the game is playable.

## Current Situation

- **State_Mushroom**: Demo state with bouncing mushroom (currently accessed via "PLAY" button)
- **Snake game logic**: Exists in `Game` class but not integrated with state system
- **Main menu**: "PLAY" button currently goes to `State_Mushroom` instead of actual game

## Goals

1. Create `State_Game` for the actual snake game
2. Move snake game logic from `Game` class into `State_Game`
3. Add "MUSHROOM" or "DEMO" button to main menu for `State_Mushroom`
4. Create `State_GameOver` as transparent overlay state
5. Implement collision detection (wall and self-collision) to trigger game over

## Plan

### 1. Create State_Game for Snake Game

**What needs to be done:**
- Create `State_Game.hpp` and `State_Game.cpp`
- Move snake game logic from `Game` class:
  - Snake movement and update logic
  - World rendering
  - Input handling (arrow keys)
  - Collision detection
- Register in `StateManager`
- Update main menu "PLAY" button to switch to `State_Game`

**Files to modify:**
- Create: `src/State_Game.hpp`, `src/State_Game.cpp`
- Modify: `src/State_MainMenu.cpp` (change PLAY button target)
- Modify: `src/StateManager.cpp` (register new state)
- Modify: `src/Game.cpp` (remove snake logic, keep only state management)

### 2. Add Mushroom Demo to Main Menu

**What needs to be done:**
- Add new button to main menu (e.g., "DEMO" or "MUSHROOM")
- Button switches to `State_Mushroom`
- Update button array from 3 to 4 buttons

**Files to modify:**
- `src/State_MainMenu.hpp` (update button arrays)
- `src/State_MainMenu.cpp` (add button, update MouseClick handler)

### 3. Create State_GameOver

**What needs to be done:**
- Create `State_GameOver.hpp` and `State_GameOver.cpp`
- Transparent overlay (like `State_Paused`)
- Display "GAME OVER" text
- Options: Restart game or return to menu
- Register in `StateManager`

**Game Over Triggers:**
- Snake hits wall
- Snake hits itself
- (Later: Lives system - when lives reach 0)

**Files to create:**
- `src/State_GameOver.hpp`
- `src/State_GameOver.cpp`

**Files to modify:**
- `src/State_Game.cpp` (detect collisions, switch to GameOver)
- `src/StateManager.cpp` (register state)
- `src/StateManager.hpp` (add `StateType::GameOver` to enum)
- `Makefile` (add object file)

### 4. Input Handling

**What needs to be done:**
- Move arrow key input from `Game::HandleInput()` to `State_Game`
- Use EventManager callbacks instead of direct polling (or keep polling for now)
- Add bindings to `keys.cfg` if using EventManager

**Files to modify:**
- `src/State_Game.cpp` (handle input)
- `keys.cfg` (if using EventManager approach)

## Implementation Order

1. Create `State_Game` and move snake logic
2. Update main menu to add Mushroom button and fix PLAY button
3. Create `State_GameOver` with basic overlay
4. Add collision detection in `State_Game` to trigger game over
5. Add restart/return to menu functionality in `State_GameOver`

## Todo

- [ ] Create `State_Game.hpp` header file
- [ ] Create `State_Game.cpp` implementation
- [ ] Move snake game logic from `Game` class to `State_Game`
- [ ] Register `State_Game` in `StateManager`
- [ ] Update main menu "PLAY" button to switch to `State_Game`
- [ ] Add "MUSHROOM" button to main menu
- [ ] Update main menu button arrays (3 → 4 buttons)
- [ ] Create `State_GameOver.hpp` header file
- [ ] Create `State_GameOver.cpp` implementation
- [ ] Add `StateType::GameOver` to enum
- [ ] Register `State_GameOver` in `StateManager`
- [ ] Implement collision detection in `State_Game` (wall + self-collision)
- [ ] Switch to `State_GameOver` on collision
- [ ] Add restart functionality in `State_GameOver`
- [ ] Add return to menu functionality in `State_GameOver`
- [ ] Update `Makefile` with new object files
- [ ] Test complete game flow: Menu → Game → GameOver → Restart/Menu

## Notes

- Keep `State_Mushroom` as a demo/test state
- `State_GameOver` should be transparent like `State_Paused` to show game underneath
- Later: Add lives system (snake has multiple lives before game over)
- Later: Add scoring system
- Later: Add high score persistence

