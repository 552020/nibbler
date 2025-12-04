# 🐛 C++ Explorer Deck — Debugging with Valgrind & GDB

_(Start after Level 2. Focus: Finding memory leaks and segfaults)_

✅ Goal: Become comfortable using valgrind and gdb to find and fix memory bugs in C++ programs.

---

## 🛠️ Setup & Tools

### Compilation with Debug Symbols

Always compile with `-g` flag for debugging:

```bash
g++ -std=c++20 -g filename.cpp -o executable
```

### Installing Tools

- **Valgrind**: `brew install valgrind` (macOS) or `sudo apt-get install valgrind` (Linux)
- **GDB**: Usually pre-installed, or `brew install gdb` / `sudo apt-get install gdb`

### Basic Commands Reference

**Valgrind:**
```bash
valgrind --leak-check=full --show-leak-kinds=all ./executable
```

**GDB:**
```bash
gdb ./executable
# Inside gdb:
# (gdb) run
# (gdb) backtrace (or bt)
# (gdb) print variable_name
# (gdb) quit
```

---

## 📋 Section A — Memory Leaks (Valgrind Focus)

### ✅ **Exercise 1: Simple Memory Leak**

- [ ] Write a program `leak1.cpp` that:
  - Allocates an integer with `new int(42)`
  - Prints the value
  - **Intentionally forgets to `delete` it**
  - Compile with `-g`
  - Run with valgrind and observe the leak report
  - Fix it by adding `delete`

### ✅ **Exercise 2: Leak in a Function**

- [ ] Write `leak2.cpp` with a function:
  ```cpp
  int* create_array(int size) {
      int* arr = new int[size];
      return arr;
  }
  ```
  - Call it in `main()` but **forget to delete the returned pointer**
  - Run valgrind, find the leak
  - Fix by deleting in `main()`

### ✅ **Exercise 3: Leak in a Loop**

- [ ] Write `leak3.cpp` that:
  - Has a loop that allocates `new int[100]` 10 times
  - **Never deletes any of them**
  - Run valgrind and see 10 leaks reported
  - Fix by deleting inside the loop

### ✅ **Exercise 4: Leak in Class Destructor**

- [ ] Write `leak4.cpp` with a class:
  ```cpp
  class DataHolder {
      int* data;
  public:
      DataHolder() { data = new int[100]; }
      // Intentionally missing destructor!
  };
  ```
  - Create objects in `main()`, run valgrind
  - Add a destructor with `delete[] data;`

---

## 💥 Section B — Segfaults (GDB Focus)

### ✅ **Exercise 5: Null Pointer Dereference**

- [ ] Write `segfault1.cpp` that:
  - Creates a `int* ptr = nullptr;`
  - **Tries to dereference it**: `*ptr = 42;`
  - Compile with `-g`
  - Run with gdb: `gdb ./segfault1`
  - Use `run` to see the crash
  - Use `backtrace` to see where it crashed
  - Fix by checking for null before dereferencing

### ✅ **Exercise 6: Out-of-Bounds Array Access**

- [ ] Write `segfault2.cpp` that:
  - Allocates `int arr[10];`
  - **Accesses `arr[15]` or `arr[-1]`**
  - Run with gdb, use `backtrace` to find the line
  - Use `print` to inspect the array bounds
  - Fix by adding bounds checking

### ✅ **Exercise 7: Use-After-Free**

- [ ] Write `segfault3.cpp` that:
  - Allocates `int* p = new int(5);`
  - Deletes it: `delete p;`
  - **Tries to use it again**: `*p = 10;`
  - Run with gdb, observe the crash
  - Fix by setting `p = nullptr;` after delete and checking before use

### ✅ **Exercise 8: Stack Overflow**

- [ ] Write `segfault4.cpp` with a recursive function:
  ```cpp
  void recurse(int n) {
      int arr[1000];  // Large stack allocation
      recurse(n + 1);  // Infinite recursion
  }
  ```
  - Call it from `main()`
  - Run with gdb, see stack overflow
  - Use `backtrace` to see the deep call stack
  - Fix by adding a base case

---

## 🔍 Section C — Combined Exercises (Both Tools)

### ✅ **Exercise 9: Multiple Bugs**

- [ ] Write `bugs1.cpp` that has:
  - A memory leak (forgot to delete)
  - A segfault (null pointer dereference)
  - Use valgrind to find the leak
  - Use gdb to find the segfault
  - Fix both

### ✅ **Exercise 10: Double Free**

- [ ] Write `bugs2.cpp` that:
  - Allocates memory: `int* p = new int(5);`
  - Deletes it: `delete p;`
  - **Deletes it again**: `delete p;`
  - Run with valgrind, observe the "invalid free" error
  - Fix by setting `p = nullptr;` after first delete

### ✅ **Exercise 11: Memory Corruption**

- [ ] Write `bugs3.cpp` that:
  - Allocates `int arr[5];`
  - **Writes beyond bounds**: `arr[10] = 99;`
  - May not crash immediately, but corrupts memory
  - Run with valgrind `--tool=memcheck`, look for "invalid write"
  - Fix by staying within bounds

### ✅ **Exercise 12: Uninitialized Memory**

- [ ] Write `bugs4.cpp` that:
  - Allocates `int* p = new int;` (not initialized)
  - **Uses it without initialization**: `std::cout << *p;`
  - Run with valgrind, look for "uninitialised value" warnings
  - Fix by initializing: `int* p = new int(0);`

---

## 🎯 Section D — Real-World Scenarios

### ✅ **Exercise 13: Class with Rule of Three Violation**

- [ ] Write `bugs5.cpp` with a class that manages dynamic memory:
  ```cpp
  class Buffer {
      int* data;
      size_t size;
  public:
      Buffer(size_t n) : data(new int[n]), size(n) {}
      // Missing copy constructor and assignment operator!
      ~Buffer() { delete[] data; }
  };
  ```
  - Create two objects, copy one to another
  - Run valgrind, observe double delete or leak
  - Implement Rule of Three (copy constructor, assignment, destructor)

### ✅ **Exercise 14: Leak in Exception Path**

- [ ] Write `bugs6.cpp` that:
  - Allocates memory: `int* p = new int[100];`
  - **Throws an exception before deleting**
  - Run valgrind, see the leak
  - Fix using RAII (wrap in a class or use `std::unique_ptr`)

### ✅ **Exercise 15: Complex Bug Hunt**

- [ ] Write `bugs7.cpp` with:
  - A class that has a memory leak
  - A function that causes a segfault
  - An array out-of-bounds access
  - Use both valgrind and gdb to find all three
  - Fix all bugs

---

## ⚙️ Section E — Advanced Debugging

### ✅ **Exercise 16: Conditional Breakpoints**

- [ ] Write a program with a loop that crashes on iteration 42
- Use gdb: `break line_number if i == 42`
- Step through with `next` and `step`
- Inspect variables with `print`

### ✅ **Exercise 17: Watchpoints**

- [ ] Write a program where a variable gets corrupted
- Use gdb: `watch variable_name`
- Run and see when it changes
- Find the culprit

### ✅ **Exercise 18: Valgrind Suppressions**

- [ ] Create a `.supp` file to suppress known false positives
- Use: `valgrind --suppressions=file.supp ./executable`
- Understand when suppressions are appropriate

---

## ✅ Completion Signal

You are ready to move forward when you can:
✔ Find memory leaks with valgrind without hesitation
✔ Use gdb to locate segfaults and inspect program state
✔ Understand valgrind error messages (leak, invalid read/write, use-after-free)
✔ Use basic gdb commands (run, backtrace, print, break, next, step)
✔ Fix common memory bugs (leaks, double free, use-after-free, out-of-bounds)

---

## 📝 Notes

- Always compile with `-g` for debugging
- Valgrind is slower — that's normal
- GDB can be intimidating at first — practice makes it easier
- Read the error messages carefully — they tell you exactly what's wrong
- Fix one bug at a time, re-run the tool after each fix

---

Copy this to `explorer_debugging.md` and tick off each exercise as you complete it.


