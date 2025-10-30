# 🧠 C++ & Rust Explorer Deck

## 📋 Rules

### Learning Principles

- **You shall use vim** - No other editors allowed
- **Write every single character yourself** - Use whatever vim gives you at your disposal
- **An exercise is passed** if you manage to write it by yourself, compile it, and the result is the expected one
- **No LLMs are allowed**
- **If you're stuck and give up** - You're still not allowed to use LLMs, but you should use official or semi-official references for the language

### Official References

- **C++**: [cppreference.com](https://cppreference.com)
- **Rust**:
  - [The Book](https://doc.rust-lang.org/book/)
  - [The Reference](https://doc.rust-lang.org/reference/)
  - [Rust by Example](https://doc.rust-lang.org/rust-by-example/)
  - [Rust Standard Library](https://doc.rust-lang.org/std/)
  - All resources available on [rust-lang.org](https://rust-lang.org/)

### Compilation Commands

- **C++**: `g++ -std=c++20 filename.cpp -o executable`
- **Rust**: `rustc filename.rs` (creates executable with same name)

### File Naming

- C++ files: `filename.cpp`
- Rust files: `filename.rs`

---

## 1. 🗓️ Daily Core (always start here)

1. **Hello program** (`hello.cpp` & `hello.rs`)

   - Write a minimal `main()` that prints "Hello, World!"

2. **String passing exploration** (`pass_arg.cpp` & `pass_arg.rs`)

   - Explore all the ways we can pass a string to a function
   - Preparation for understanding input and output string handling
   - **C++**: Test different parameter types: `string`, `string&`, `const string&`, `string*`
   - **Rust**: Understand borrowing system - this step explains `std::io::stdin().read_line(&mut name)` where `&mut` introduces mutable borrowing

3. **Input & output** (`greet.cpp`)

   - Ask for a name, store in a string, print "Hello, name!"
   - Create three different versions of greeting someone: one without an extra greet function, and two with greet functions
   - Create two different greet functions:

     - One that prints directly (void return)
     - One that returns the string to be printed by main

   - Basically, at the end you should have a main where the user is greeted three times but inputs their name only once.

4. **Input & output with loop** (`loop.cpp`)

   - Ask "What's your name?" twice using a for loop
   - First time: use normal greet (returns string)
   - Second time: use void greet function

---

## 2. 🧩 Data & Functions

- [ ] **Struct practice**

  - Define `struct Point { int x, y; };`
  - Create, assign, print.

- [ ] **Function refresher**

  - Write a function `int add(int, int)` and call it.

- [ ] **Const correctness**

  - Add a `const` function and verify compiler enforces it.

---

## 3. 🧱 Classes & Lifetime

- [ ] **Simple class**

  - Make a `Player` with constructor, `move()`, and `print()`.

- [ ] **Rule of Three**

  - Add copy constructor, copy assignment operator, and destructor.
  - Print debug messages to see which one is called.

- [ ] **Rule of Five (optional)**

  - Add move constructor and move assignment.

- [ ] **Header / source split**

  - Put declaration in `.hpp`, definitions in `.cpp`, include it in `main.cpp`.

---

## 4. 🔁 Polymorphism & Interfaces

- [ ] **Virtual vs. non-virtual**

  - Create base `A`, derived `B`, both with `f()`.
  - Test with `A* a = new B(); a->f();`

- [ ] **Pure virtual**

  - Make `Shape` with `draw() = 0`; subclass `Circle` and `Square`.
  - Store pointers in a `std::vector<Shape*>` and call `draw()` polymorphically.

- [ ] **Interface naming**

  - Write `class IRenderer` with `draw()` pure virtual.
  - Derive `ConsoleRenderer` and override `draw()`.

---

## 5. ⏱️ Game-Loop Foundations

- [ ] **Timer & loop**

  - Use `std::chrono` and `std::this_thread::sleep_until` for a fixed 10 Hz loop.

- [ ] **Game state**

  - Define `GameState` with width, height, and `Point head`.

- [ ] **Renderer abstraction**

  - Implement `ConsoleRenderer::draw(const GameState&)` that prints the head position.

---

## 6. 🧮 Fun Challenge

- [ ] **Turing Machine**

  - A good exercise would be to write a turing machine. Less than 100 lines of code, simple logic but very exciting

## 7. ⚙️ Extra (when the basics feel smooth)

- [ ] Re-implement the same exercises using modern C++20 features (`auto`, range-for, structured bindings).
- [ ] Add comments explaining each keyword (`virtual`, `override`, `const`, `explicit`).
- [ ] Try compiling with `-Wall -Wextra -pedantic` and fix all warnings.

---

You can copy this into a file like `cpp_explorer.md`
and mark each task you master:

```md
- [x] Hello program
- [x] Input & output
- [ ] Virtual vs. non-virtual
```
