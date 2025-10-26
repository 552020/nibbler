Perfect — here’s **Level 2** of your C++ daily deck.
This set builds directly toward your **Snake + dynamic-library** project.

---

# 🧠 C++ Refresher Deck — Level 2

_(Start once Level 1 feels automatic.)_

---

## 🧮 Memory & Resource Management

- [ ] **RAII concept**

  - Write a small `FileGuard` class that opens a file in its constructor and closes it in its destructor.
  - Observe how it closes automatically even on `return` or `throw`.

- [ ] **Smart pointers**

  - Replace raw `new/delete` with `std::unique_ptr` and `std::make_unique`.
  - Pass smart pointers to functions by reference (`const&`).

- [ ] **Dynamic allocation**

  - Allocate an array with `new[]`, then convert it to `std::vector<int>`.

---

## 🧩 Modules & Organization

- [ ] **Separate interface/implementation**

  - Put a class in `Foo.hpp` + `Foo.cpp`; compile both.

- [ ] **Namespaces**

  - Wrap a few utility functions inside `namespace game { ... }` and call them.

- [ ] **Enums & strongly-typed enums**

  - Compare classic `enum` vs. `enum class`.

---

## 🧱 Advanced Classes

- [ ] **Copy vs Move demonstration**

  - Make a class that prints messages in each constructor/assignment to see the Rule of Five in action.

- [ ] **Operator overloading**

  - Overload `operator==` or `operator<<` for your `Point` struct.

---

## 🧭 Design Patterns Prep

- [ ] **Interface + implementation pair**

  - Create an abstract `IGui` with pure virtual `init()`, `draw()`, `pollInput()`.
  - Implement `ConsoleGui` that just prints text.

- [ ] **Factory function**

  - Write `create_gui()` returning `std::unique_ptr<IGui>`.

---

## 🔗 Dynamic Libraries (Plugins)

- [ ] **Minimal plugin experiment**

  - Write one header with:

    ```cpp
    struct IHello { virtual void say() = 0; virtual ~IHello() = default; };
    extern "C" IHello* create();
    extern "C" void destroy(IHello*);
    ```

  - Build a shared library (`g++ -std=c++20 -fPIC -shared hello.cpp -o libhello.so`).
  - Load it from another program using `dlopen` + `dlsym`.
  - Call `say()`.

- [ ] **Version check**

  - Add an integer `API_VERSION` and verify it before calling.

- [ ] **Hot-swap simulation**

  - Write a loop that loads one plugin, calls it, unloads, and loads another.

---

## 🎮 Toward Snake

- [ ] **Combine loop + renderer**

  - Move your Level 1 game loop into its own class `GameEngine`.

- [ ] **Pass state to renderer**

  - Have the engine own a pointer to `IGui`; call `gui->draw(state)` each tick.

- [ ] **Key handling abstraction**

  - Define an `enum class Input { Up, Down, Left, Right, Quit };`
  - Implement a console version that reads from `std::cin`.

- [ ] **Test swapping renderers**

  - Compile two shared-library renderers and switch between them by key press.

---

## ⚙️ Optional Extensions

- [ ] File I/O – save and load high scores using `std::ofstream` / `std::ifstream`.
- [ ] Error handling – use `std::optional` or `std::expected`-style returns.
- [ ] Timing – add FPS or tick counters with `std::chrono`.

---

Copy it to `cpp_daily_refresher_level2.md` and tick off what you master.

Would you like me to prepare a **Level 3** (focused purely on the dynamic plugin system + ncurses integration) next?
