Title: Mini Project – Static vs Dynamic Libraries

## Overview

This project demonstrates the difference between static and dynamic linking using simple library examples. The basic "hello1/2/3" example shows the technical mechanics, but the **enhanced scenarios** below provide more meaningful use cases that illustrate _why_ you would choose different libraries at compile-time or runtime.

---

## 🎯 Recommended Scenarios

The simple "hello" libraries prove static vs dynamic linking technically, but they don't feel meaningful. Here are better tiny scenarios—still simple, but they _make sense_ as reasons to switch libraries:

### 📊 Scenario Comparison

| Scenario           | Simple | Makes sense | Good for learning dynamic linking |
| ------------------ | ------ | ----------- | --------------------------------- |
| Hello1/2/3         | ✔      | ✘           | ✔                                 |
| Sorting algorithms | ✔      | ✔✔✔         | ✔✔                                |
| Math flavors       | ✔      | ✔✔          | ✔                                 |
| Renderer plugins   | ✔✔     | ✔✔✔         | ✔✔✔                               |
| Logging formats    | ✔✔     | ✔✔✔         | ✔✔✔                               |

**Best combination of simplicity + meaning:** **Sorting algorithms** or **Logging format plugins**

---

## 🚀 Enhanced Scenario 1: Sorting Algorithms (Recommended)

**Library1:** bubble sort  
**Library2:** quicksort  
**Library3:** mergesort

All libraries expose the same function:

```c
void sort(int *arr, int size);
```

Your program:

- Lets user input an array
- Lets user select which algorithm to use (1, 2, or 3)
- Dynamically loads the chosen library
- Calls `sort()`

💡 **Why it's better:**

- It's still small (like hello example)
- But now there's a **real reason** to switch libraries
- Some algorithms are faster, some simpler
- Demonstrates runtime algorithm selection

---

## 📝 Enhanced Scenario 2: Logging Format Plugins (Recommended)

Libraries:

| Library            | Behavior                                     |
| ------------------ | -------------------------------------------- |
| liblogger_plain.so | prints `"INFO: message"`                     |
| liblogger_json.so  | prints `{ "level": "info", "message": ... }` |
| liblogger_color.so | ANSI colored output                          |

All export:

```c
void log_info(const char* msg);
```

💡 **Why it works:**

- Logging is a real common case where people swap libraries
- Represents real plugin idea (different output formats)
- Still tiny and simple
- Demonstrates runtime extension

---

## 🧮 Enhanced Scenario 3: Math Libraries

- `libmath_simple.so` → add, subtract
- `libmath_scientific.so` → sin, cos, sqrt, pow
- `libmath_stats.so` → average, variance, median

Each library exports:

```c
double compute(double a, double b);    // Or different functions
```

Your program loads a different library based on user choice.

💡 **Why it works:**

- Libraries represent **different capabilities**
- Shows possible modular design
- Same API, different functionality

---

## 🖼 Enhanced Scenario 4: Graphics Renderer Plugins

- `librender_ascii.so` → prints shapes using ASCII art
- `librender_unicode.so` → prints Unicode shapes
- `librender_color.so` → prints shapes with ANSI colors

All export:

```c
void draw_square(int size);
```

Your program asks user which "renderer" to use.

💡 **Why it works:**

- Represents real plugin idea (rendering in different formats)
- Still tiny and simple
- Demonstrates runtime extension

---

## 📋 Basic Example: Hello Libraries (Simple but Less Meaningful)

The original "hello1/2/3" example is included below for completeness. It demonstrates the technical mechanics but lacks a meaningful use case.

### Todo list:

1. Setup

   - Create a folder, e.g. `lib-hello-test/`.
   - Inside, create subfolders: `src/`, `build/`, `lib/`.

2. Library sources

   - In `src/hello1.c`:

     - Define `void hello(void)` printing `"Hello from library 1\n"`.

   - In `src/hello2.c`:

     - Same `void hello(void)` printing `"Hello from library 2\n"`.

   - In `src/hello3.c`:

     - Same `void hello(void)` printing `"Hello from library 3\n"`.

   - (Optional) One header `src/hello.h` with:

     - `void hello(void);`

3. Build static libraries (.a)

   - Compile objects:

     - `gcc -c src/hello1.c -o build/hello1.o`
     - `gcc -c src/hello2.c -o build/hello2.o`
     - `gcc -c src/hello3.c -o build/hello3.o`

   - Archive into static libs:

     - `ar rcs lib/libhello1.a build/hello1.o`
     - `ar rcs lib/libhello2.a build/hello2.o`
     - `ar rcs lib/libhello3.a build/hello3.o`

4. Build shared libraries (.so/.dylib)

   - Recompile objects as PIC:

     - `gcc -fPIC -c src/hello1.c -o build/hello1_pic.o`
     - `gcc -fPIC -c src/hello2.c -o build/hello2_pic.o`
     - `gcc -fPIC -c src/hello3.c -o build/hello3_pic.o`

   - Create shared libs:

     - On Linux:

       - `gcc -shared -o lib/libhello1.so build/hello1_pic.o`
       - `gcc -shared -o lib/libhello2.so build/hello2_pic.o`
       - `gcc -shared -o lib/libhello3.so build/hello3_pic.o`

     - On macOS:

       - `gcc -dynamiclib -o lib/libhello1.dylib build/hello1_pic.o`
       - `gcc -dynamiclib -o lib/libhello2.dylib build/hello2_pic.o`
       - `gcc -dynamiclib -o lib/libhello3.dylib build/hello3_pic.o`

5. Static version – three executables

   - Create `src/main_static.c`:

     - Declare `void hello(void);`
     - In `main`, call `hello();`.

   - Build three binaries, each linked to a different `.a`:

     - `gcc src/main_static.c -Llib -lhello1 -o app_static1`
     - `gcc src/main_static.c -Llib -lhello2 -o app_static2`
     - `gcc src/main_static.c -Llib -lhello3 -o app_static3`

   - Compare sizes:

     - `ls -lh app_static*`

6. Dynamic version – one executable, user chooses library

   - Create `src/main_dynamic.c`:

     - Ask user: “1, 2 or 3?”
     - Build library path string based on input (e.g. `"lib/libhello2.so"` / `.dylib`).
     - Use `dlopen`, `dlsym`, `dlclose`:

       - `dlopen(path, RTLD_NOW);`
       - `dlsym(handle, "hello");`
       - call function pointer `void (*hello_fn)(void)`.

   - Compile and link (Linux):

     - `gcc src/main_dynamic.c -ldl -o app_dynamic`

   - On macOS:

     - `gcc src/main_dynamic.c -o app_dynamic`
       (no `-ldl`, functions are in libSystem)

7. Run and observe

   - Static:

     - `./app_static1`, `./app_static2`, `./app_static3`
       → each prints different text, each binary has its own copy of code.

   - Dynamic:

     - `./app_dynamic`
       → choose 1/2/3 at runtime, loads different library, same executable.

   - Compare sizes:

     - `ls -lh app_static* app_dynamic lib/*`

8. (Optional) Makefile

   - Write a small Makefile with targets:

     - `static-libs`, `shared-libs`, `app_static1/2/3`, `app_dynamic`, `clean`.

---

## 🎓 Implementing Enhanced Scenarios

### For Sorting Algorithms Scenario:

**Library sources:**

- `src/sort_bubble.c`: Implement bubble sort algorithm
- `src/sort_quick.c`: Implement quicksort algorithm
- `src/sort_merge.c`: Implement mergesort algorithm

All implement:

```c
void sort(int *arr, int size);
```

**Main program (`src/main_dynamic.c`):**

- Prompt user for array size and values
- Ask: "Choose algorithm: 1=Bubble, 2=Quick, 3=Merge"
- Build library path: `"lib/libsort_bubble.so"` / `.dylib` etc.
- Use `dlopen`, `dlsym` to load and call `sort()`
- Display sorted array

**Benefits:**

- Same executable, different algorithms at runtime
- Compare performance: `time ./app_dynamic` with different choices
- See how static linking embeds algorithm, dynamic loads it

---

### For Logging Format Scenario:

**Library sources:**

- `src/logger_plain.c`: Simple `printf("INFO: %s\n", msg)`
- `src/logger_json.c`: `printf("{\"level\":\"info\",\"message\":\"%s\"}\n", msg)`
- `src/logger_color.c`: ANSI escape codes for colored output

All implement:

```c
void log_info(const char* msg);
```

**Main program (`src/main_dynamic.c`):**

- Ask user: "Choose logger: 1=Plain, 2=JSON, 3=Color"
- Load chosen library dynamically
- Call `log_info("Test message")` to see different formats

**Benefits:**

- Real-world use case (logging is commonly pluggable)
- Same code, different output formats
- Easy to add new formats (just create new library)

---

## 💡 Key Takeaways

1. **Static linking**: Algorithm/format is chosen at compile-time, embedded in binary

   - Result: Three separate executables, each with its own copy
   - Size: Larger binaries, but no runtime dependency

2. **Dynamic linking**: Algorithm/format is chosen at runtime

   - Result: One executable, loads library on demand
   - Size: Smaller executable, but requires library files at runtime
   - Flexibility: Can swap libraries without recompiling

3. **When to use each:**
   - **Static**: When you know exactly what you need at compile-time
   - **Dynamic**: When you want flexibility, plugins, or smaller binaries
