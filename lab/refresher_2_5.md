Great — here is a **Level 2.5: Pure Refresher on C++ Classes, OOP, and Memory Management** before we move to plugins or Snake.

You can add this between Level 2 and Level 3 in your learning plan.

---

# 🧠 C++ Refresher Deck — Level 2.5

_(Focus: Classes, constructors, copy/move, memory, no graphics yet)_

✅ Goal: Be completely comfortable again with writing and understanding C++ classes, constructors, destructors, copy behavior, headers, etc.

---

### ✅ **Section A — Class Fundamentals**

- [ ] Write a simple class `Player` with:

  - private: `std::string name; int score;`
  - public:

    - constructor: `Player(std::string n)`
    - method: `void print() const;`

- [ ] Separate it into `.hpp` (declaration) and `.cpp` (implementation).
- [ ] Create an object in `main()`, call its methods.

---

### ✅ **Section B — Canonical Form (Rule of Three / Five)**

Make a class `Buffer` that manages a dynamic array manually:

```cpp
class Buffer {
private:
    int* data;
    size_t size;
public:
    Buffer(size_t n);                     // constructor
    Buffer(const Buffer& other);          // copy constructor
    Buffer& operator=(const Buffer& other); // copy assignment
    ~Buffer();                            // destructor
};
```

- [ ] Implement all four functions with `std::cout` prints to see when each is called.
- [ ] Create, copy, assign, and destroy objects in `main()`, observe order.

**Optional modern upgrade:**

- Add move constructor and move assignment (`Buffer(Buffer&&)`, `operator=(Buffer&&)`).

---

### ✅ **Section C — `struct` vs `class`**

- [ ] Create a `struct Point { int x, y; };`
- [ ] Create a `class Point2` with same fields but private + public getters/setters.
- [ ] Understand: only difference is default `public` vs `private`.

---

### ✅ **Section D — `virtual`, Polymorphism & Interfaces**

- [ ] Write:

  ```cpp
  class Animal {
  public:
      virtual void speak() { std::cout << "Animal\n"; }
      virtual ~Animal() = default;
  };

  class Dog : public Animal {
  public:
      void speak() override { std::cout << "Dog\n"; }
  };
  ```

- [ ] In `main()`:

  ```cpp
  Animal* a = new Dog();
  a->speak();   // prints "Dog"
  delete a;
  ```

- [ ] Change `virtual void speak() = 0;` to make `Animal` abstract — can’t instantiate.

---

### ✅ **Section E — Smart Pointers Refresher**

- [ ] Replace `new` and `delete` with:

  ```cpp
  std::unique_ptr<Animal> a = std::make_unique<Dog>();
  a->speak();
  ```

- [ ] Try passing `std::unique_ptr<T>` to functions as

  - `T*` (raw pointer, no ownership)
  - `std::unique_ptr<T>&&` (transfer ownership)

---

### ✅ **Section F — Namespaces & Headers**

- [ ] Put your class in a namespace:

  ```cpp
  namespace game {
      class Player { ... };
  }
  ```

- [ ] Call it as `game::Player p("Alice");`

---

### ✅ **Completion Signal**

You are ready to move to **Level 3 (dynamic libraries + ncurses)** when you can:
✔ Write a class with constructor, destructor, copy, move
✔ Use `override`, `virtual`, and abstract classes intentionally
✔ Manage pointers with RAII / `unique_ptr`
✔ Split into `.hpp` and `.cpp` without thinking

---

Would you like me to prepare **small example code files** for each exercise so you can start writing immediately?
