# 🐍 Nibbler Practice Project

_(Dynamic libraries + ncurses integration)_

---

## 🔌 Plugin Architecture Core

- [ ] **Shared interface header**

  - Create `igui.hpp` with:

    ```cpp
    struct GameView { int w, h; std::vector<Point> snake; Point food; };
    enum class Input { None, Up, Down, Left, Right, Quit };
    struct IGui {
        virtual ~IGui() = default;
        virtual bool init(int w,int h,int cell)=0;
        virtual Input pollInput()=0;
        virtual void render(const GameView&)=0;
        virtual void shutdown()=0;
    };
    extern "C" IGui* create_gui();
    extern "C" void destroy_gui(IGui*);
    ```

  - Ensure no graphics headers appear here.

- [ ] **Core loader**

  - Write a small loader class that:

    - uses `dlopen`, `dlsym`, `dlclose`;
    - stores function pointers for `create_gui` / `destroy_gui`;
    - creates and owns one `IGui*`.

  - Test loading and unloading one mock plugin.

- [ ] **Hot-swap test**

  - Map keys 1–3 to unload current GUI and load another shared library.
  - Verify game state persists.

---

## 🧱 ncurses Plugin

- [ ] **Minimal window**

  - In `plugin_ncurses.cpp`:

    - call `initscr()`, `cbreak()`, `noecho()`, `curs_set(0)`;
    - draw a single character at (x, y).

  - Build as:
    `g++ -std=c++20 -fPIC -shared plugin_ncurses.cpp -o libgui_ncurses.so -lncurses`.

- [ ] **Implement IGui methods**

  - `init()` → setup ncurses
  - `pollInput()` → use `getch()` to map keys to `Input` enum
  - `render()` → clear screen, draw snake and food, refresh()
  - `shutdown()` → `endwin()`

- [ ] **Integration test**

  - Load `libgui_ncurses.so` from your core loader, run a loop, move the head with WASD.

---

## 🖼️ Future Renderers (Preview)

- [ ] **Stub raylib plugin**

  - Copy interface; in `init()` call `InitWindow()`, in `render()` draw colored rectangles.

- [ ] **Stub SDL2 plugin**

  - Initialize SDL, draw a rectangle for snake head.

- [ ] Confirm that switching 1/2/3 works without restarting game.

---

## 🧠 Architecture Checks

- [ ] Ensure the core never includes any graphics headers.
- [ ] Confirm that all plugin functions use `extern "C"`.
- [ ] Add a compile-time `API_VERSION` constant in `igui.hpp` and verify on load.
- [ ] Practice compiling everything with:

  ```bash
  g++ -std=c++20 -Wall -Wextra -pedantic ...
  ```

---

## ⚙️ Optional Advanced

- [ ] Add error handling for `dlerror()` results.
- [ ] Implement a `std::unique_ptr<IGui, Deleter>` for automatic cleanup.
- [ ] Add FPS or tick display to ncurses render.
- [ ] Store plugins in `/plugins/` folder and load by filename pattern.

---

When you can:

- write the interface header from memory,
- compile a plugin with ncurses,
- load/unload it via `dlopen`,
- and see your snake head move,

→ you’re ready to start the **full multi-GUI Snake project**.

Would you like me to prepare **Level 4**, where we start building the actual _Snake gameplay logic_ (movement, growth, collisions, score)?
