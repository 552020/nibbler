# Learnings

## SFML 3.x API Changes

- `sf::Sprite` no longer has default constructor - must be constructed with texture
- `sf::Texture` can be loaded via constructor: `sf::Texture("path/to/file.png")`
- Fullscreen is now `sf::State::Fullscreen`, not `sf::Style::Fullscreen`
- `sf::Uint32` removed - use `std::uint32_t` instead
- Event polling returns `std::optional<Event>` (C++17)

## C++ Concepts

- **RAII**: Resources are automatically cleaned up when objects go out of scope
- **Rule of Five**: For non-copyable classes (like `sf::RenderWindow`), delete copy/move operations
- **Initializer lists**: Use for member initialization, especially when members don't have default constructors
- **std::optional**: C++17 feature for values that may or may not exist

## Common Bugs

- **Rendering on closed window**: Always use `window.isOpen()` as loop condition, not a separate flag
- **Destruction order**: Members destroyed in reverse declaration order
- **Texture lifetime**: Sprite must outlive texture (or texture must outlive sprite)

## Best Practices

- Use `window.isOpen()` for loop condition (idiomatic SFML pattern)
- Let RAII handle cleanup - don't manually close in destructors unless necessary
- Initialize members in initializer list when they don't have default constructors

