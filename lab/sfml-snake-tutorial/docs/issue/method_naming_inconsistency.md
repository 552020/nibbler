# Method Naming Inconsistency: Tick() vs Update()

## Problem Summary
There is a naming inconsistency in the game update methods:
- `Snake` class uses `Tick()` for its update logic
- `World` class uses `Update()` for its update logic

Both methods serve the same purpose (updating game state each frame/timestep) but have different names.

## Current Implementation

### Snake Class
```cpp
void Tick(); // Update method.
```
- Called from `Game::Update()` as `m_snake.Tick()`
- Handles snake movement and internal state updates

### World Class
```cpp
void Update(Snake& l_player);
```
- Called from `Game::Update()` as `m_world.Update(m_snake)`
- Handles apple collision detection and boundary collision detection

## Issue
Both methods are part of the game loop update cycle but use inconsistent naming:
- `Tick()` is commonly used for per-frame/timestep updates
- `Update()` is also commonly used for the same purpose

This inconsistency makes the codebase less uniform and could be confusing for developers.

## Questions to Consider
1. Should both methods be renamed to `Update()` for consistency?
2. Should both methods be renamed to `Tick()` for consistency?
3. Is there a semantic difference that justifies different names?
   - `Tick()` might imply a single game tick/timestep
   - `Update()` might be more general

## Status
**Open** - Needs discussion and decision on preferred naming convention.

