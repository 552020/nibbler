# SFML Snake Tutorial (Chapters 1-5)

This project implements the Snake game tutorial from **SFML Game Development By Example** by Artur Moreira, covering **Chapters 1 through 5**.

## Overview

This is a complete Snake game implementation with:
- State management system (StateManager, BaseState)
- Event-driven input handling (EventManager)
- Multiple game states (Intro, MainMenu, Game, Paused, GameOver, Mushroom)
- Window management and rendering
- Snake game logic with collision detection
- World/level management

## Chapters Covered

- **Chapter 1**: Introduction to SFML and basic window setup
- **Chapter 2**: Time, movement, and sprites
- **Chapter 3**: Sprite animation and game loop
- **Chapter 4**: Input handling and event management
- **Chapter 5**: State management and game states

## Project Structure

```
src/
├── main.cpp              # Entry point
├── Game.cpp/hpp          # Main game class
├── Window.cpp/hpp         # Window management
├── EventManager.cpp/hpp   # Event handling system
├── StateManager.cpp/hpp   # State management system
├── BaseState.cpp/hpp      # Base state class
├── State_*.cpp/hpp        # Individual game states
├── Snake.cpp/hpp          # Snake game logic
├── World.cpp/hpp          # World/level management
└── TextBox.cpp/hpp        # Text rendering
```

## Building

See `Makefile` for build instructions. The project uses SFML 3.x and requires:
- C++17 compiler
- CMake (for building SFML)
- SFML libraries (automatically cloned and built)

## Next Steps

**Chapter 6** introduces a new platformer game project with:
- SFML views and screen scrolling
- Automated resource management
- Sprite sheets and animation systems

The platformer tutorial continues in a separate project directory.

