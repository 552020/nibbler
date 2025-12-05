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

## Implementation Progress

### First Step: Utilities.h

The first implementation in this new project is **`Utilities.h`**, which provides the `GetWorkingDirectory()` function. This is essential because:

- **Problem**: When loading resources (textures, sounds, config files) with relative paths, the working directory can vary depending on how/where the program is launched (terminal, IDE, different folder, etc.)

- **Solution**: `GetWorkingDirectory()` returns the directory where the executable is located, ensuring resource paths are always relative to the executable location, not the current working directory

- **Usage**: 
  ```cpp
  std::string basePath = Utils::GetWorkingDirectory();
  texture.loadFromFile(basePath + "assets/player.png");  // Always works!
  ```

This provides consistent, reliable resource loading regardless of where the program is launched from, which is crucial for the platformer game's asset management system.

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
