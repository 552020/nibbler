# SFML Platformer Tutorial (Chapters 6+)

This project implements the platformer game tutorial from **SFML Game Development By Example** by Artur Moreira, covering **Chapter 6 and onwards**.

## Overview

This is a platformer game implementation featuring:
- Knight and Rat character sprites
- Platformer tilesets and backgrounds
- SFML views and screen scrolling
- Automated resource management (ResourceManager, TextureManager)
- Sprite sheets and animation systems
- Entity management and collision detection
- Game map system with tiles

## Chapters Covered

- **Chapter 6**: Views, resource management, sprite sheets, and animation
- **Chapter 7**: Game map design, entity management, and collision detection
- **Chapter 8+**: (To be added as tutorial progresses)

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
├── Utilities.h           # Working directory utilities
├── ResourceManager.h      # Template resource manager
├── TextureManager.cpp/hpp # Texture resource management
├── SpriteSheet.cpp/hpp    # Sprite sheet handling
├── Anim_*.cpp/hpp         # Animation classes
└── ...                    # Additional platformer-specific classes
```

## Building

See `Makefile` for build instructions. The project uses SFML 3.x and requires:
- C++17 compiler
- CMake (for building SFML)
- SFML libraries (automatically cloned and built)

## Assets

The project uses the following open-source assets:
- Lemcraft by richtaur (CC0 1.0)
- Prototyping 2D Pixelart Tilesets by robotality (CC-BY-SA 3.0)
- Generic Platformer Tileset by etqws3 (CC0 1.0)
- Knight and Rat sprites by backyardninja

## Previous Project

The **Snake game tutorial (Chapters 1-5)** is available in `../sfml-snake-tutorial/`.
