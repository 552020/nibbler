# 🧠 C++ Refresher Deck

## 🗓️ Daily Core (always start here)

1. **Hello program**

   - Write a minimal `main()` that prints "Hello, World!"
   - Program should be called `hello.cpp`
   - Compile with `g++ -std=c++20 hello.cpp -o hello`

2. **Input & output**

   - Ask for a name, store in a string, print "Hello, name!"
   - Create three different versions (of ways of greeting someone), one without an extra greet function, and two with two greet functions
   - Create two different greet functions:

     - One that prints directly (void return)
     - One that returns the string to be printed by main

   - Basically at the end you should have a main and the user should be greated three times and input their name just 1 time though.

3. **Input & output with loop**

   - Ask "What's your name?" twice using a for loop
   - First time: use normal greet (returns string)
   - Second time: use void greet function

---

## 🧩 Data & Functions

- [ ] **Struct practice**

  - Define `struct Point { int x, y; };`
  - Create, assign, print.

- [ ] **Function refresher**

  - Write a function `int add(int, int)` and call it.

- [ ] **Const correctness**

  - Add a `const` function and verify compiler enforces it.

---

## 🧱 Classes & Lifetime

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

## 🔁 Polymorphism & Interfaces

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

## ⏱️ Game-Loop Foundations

- [ ] **Timer & loop**

  - Use `std::chrono` and `std::this_thread::sleep_until` for a fixed 10 Hz loop.

- [ ] **Game state**

  - Define `GameState` with width, height, and `Point head`.

- [ ] **Renderer abstraction**

  - Implement `ConsoleRenderer::draw(const GameState&)` that prints the head position.

---

## 🧮 Fun Challenge

- [ ] **Turing Machine**

  - A good exercise would be to write a turing machine. Less than 100 lines of code, simple logic but very exciting

## ⚙️ Extra (when the basics feel smooth)

- [ ] Re-implement the same exercises using modern C++20 features (`auto`, range-for, structured bindings).
- [ ] Add comments explaining each keyword (`virtual`, `override`, `const`, `explicit`).
- [ ] Try compiling with `-Wall -Wextra -pedantic` and fix all warnings.

---

You can copy this into a file like `cpp_daily_refresher.md`
and mark each task you master:

```md
- [x] Hello program
- [x] Input & output
- [ ] Virtual vs. non-virtual
```
