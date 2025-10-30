# std::getline Function

## Purpose

`std::getline` reads a line of text from an input stream until it encounters a newline character (`\n`) or reaches the end of the stream.

## Syntax

```cpp
std::getline(stream, string_variable)
```

## Example Usage

```cpp
std::string name;
std::getline(std::cin, name);
```

## What it does

1. **Reads from `std::cin`** - the standard input stream (keyboard input)
2. **Stores the result in `name`** - your `std::string` variable
3. **Reads until newline** - it will read everything the user types until they press Enter
4. **Discards the newline** - the `\n` character is read but not stored in the string

## Key Advantages over `std::cin >>`

1. **Handles spaces**: Unlike `std::cin >> name`, `getline` can read names with spaces (e.g., "John Doe")
2. **Reads entire line**: It captures everything until Enter is pressed
3. **No buffer issues**: Avoids problems with leftover newline characters in the input buffer

## Example Behavior

- User types: `Stefano Rossi` and presses Enter
- `name` will contain: `"Stefano Rossi"`
- The newline character is consumed but not stored

## Alternative Syntax

You can also specify a delimiter:

```cpp
std::getline(std::cin, name, ',');  // Reads until comma
```

But the default behavior (reading until newline) is perfect for getting a user's full name.

## Why Use std::getline?

This function is ideal for reading user input that may contain spaces, making programs more robust than using the extraction operator `>>`.
