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
- **Sprite with empty texture**: If sprite is constructed with empty texture in initializer list, then texture is loaded later, the sprite will have 0x0 bounds and won't render
  - **Solution**: After loading texture, call `sprite.setTexture(texture, true)` with `resetRect=true` to update sprite bounds
  - **Better solution**: Load texture before constructing sprite, or use texture constructor that loads from file
  - This was encountered with both mushroom sprite and intro sprite - same pattern, same fix

## Best Practices

- **CRITICAL: Use `window.isOpen()` for loop condition, NOT `IsDone()` flag**
  - Using `IsDone()` causes segfault: when window closes, `IsDone()` is set to true, but loop still calls `Render()` on closed window
  - `IsOpen()` exits loop immediately when window closes, preventing render on closed window
  - This was a hard-learned lesson - always use `IsOpen()` for main game loop condition
- Let RAII handle cleanup - don't manually close in destructors unless necessary
- Initialize members in initializer list when they don't have default constructors

