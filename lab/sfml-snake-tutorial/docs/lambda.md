# Understanding Lambdas in StateManager::RegisterState

## Overview

This document explains the lambda function used in `StateManager::RegisterState()` and how it relates to the state factory pattern.

## The Code in Question

```cpp
template<class T>
void StateManager::RegisterState(const StateType& l_type) {
    static_assert(std::is_base_of_v<BaseState, T>,
                  "T must derive from BaseState");
    m_stateFactory[l_type] = [this]() -> BaseState* {
        return new T(this);
    };
}
```

The right side of the assignment contains a **lambda function** (anonymous function) that is stored in a `std::function<BaseState*(void)>`.

---

## Part 1: What is a Lambda?

### Definition

A **lambda** is an anonymous function created inline. It allows you to define a function without giving it a name.

### Basic Lambda Syntax

```cpp
[capture](parameters) -> return_type {
    body
}
```

### Breaking Down the RegisterState Lambda

```cpp
[this]() -> BaseState* {
    return new T(this);
}
```

| Part | Meaning |
|------|---------|
| `[this]` | Capture `this` pointer (StateManager*), so we can use it inside the lambda |
| `()` | Lambda takes no parameters |
| `-> BaseState*` | It returns a `BaseState*` |
| `{ return new T(this); }` | When called, it creates and returns `new T(this)` |

### Equivalent Named Function

This lambda is equivalent to writing:

```cpp
BaseState* createStateFunction() {
    return new T(this);
}
```

But we write it *inline* instead of naming it.

---

## Part 2: Why Use a Lambda Here?

### The StateFactory Type

`m_stateFactory` stores **functions**, not objects:

```cpp
using StateFactory = std::unordered_map<
    StateType,
    std::function<BaseState*(void)>
>;
```

The value for each key must be a function that:
- Takes **no parameters**
- Returns **BaseState***

The lambda matches that signature exactly.

### Visual Representation

```
m_stateFactory:

Key (StateType)   → Value (function to create state)
-------------------------------------------------------
Game              → function() { return new StateGame(this); }
Paused            → function() { return new StatePaused(this); }
Intro             → function() { return new StateIntro(this); }
-------------------------------------------------------
```

### Expanded Form

You can imagine this line rewritten as:

```cpp
std::function<BaseState*(void)> func =
    [this]() -> BaseState* {
        return new T(this);
    };

m_stateFactory[l_type] = func;
```

Same thing — just expanded for clarity.

---

## Part 3: Why Capture `[this]`?

### Every State Needs StateManager

Every State (like `StateGame`, `StatePaused`) needs a pointer to the StateManager in its constructor:

```cpp
StateGame::StateGame(StateManager* l_stateManager) 
    : BaseState(l_stateManager) {}
```

### Why States Need StateManager

States need to be able to:
- Switch to other states (e.g., from Game → Pause)
- Request to be popped, pushed, or removed
- Access SharedContext (window, event manager, etc.), which is stored in StateManager
- Communicate with other states if needed

### The Pointer Storage

In `BaseState`, we have:

```cpp
protected:
    StateManager* m_stateMgr;
```

### In the Lambda

When we write:

```cpp
return new T(this);
```

- `T` = the state class (e.g. `StateGame`, `StateMenu`)
- `this` = pointer to the current StateManager
- So `new T(this)` means: create a new State object, and give it the pointer to StateManager

### Example Usage in States

Without passing StateManager, you could not do:

```cpp
void StateGame::Pause() {
    m_stateMgr->SwitchTo(StateType::Paused);
}
```

or:

```cpp
m_stateMgr->Remove(StateType::GameOver);
```

or access shared resources:

```cpp
m_stateMgr->GetContext()->m_wind->GetWindow();
```

---

## Part 4: Lambdas vs Normal Functions

### Normal Named Function

```cpp
void f() {
    std::cout << "Hello\n";
}

f();  // call it
```

- `f` is the **name** of the function
- Defined at **global scope** (or inside a class/namespace)
- Exists independently
- Cannot be created dynamically inside another function
- Cannot carry values from where it was created unless passed manually

### Lambda Assigned to Variable

```cpp
auto f = []() {
    std::cout << "Hello Lambda\n";
};

f();  // call it
```

- `f` is **not a function name**, but a **variable**
- The lambda has **no name** — it is anonymous
- `f` holds a **callable object** (technically, a hidden type created by the compiler)
- The lambda can be created **inside functions**, even inside loops
- It can **capture local variables** (via `[ ]`), which normal functions cannot do

### Key Differences

| Feature | Normal Function | Lambda assigned to variable |
|---------|----------------|----------------------------|
| Has a name? | Yes (`f`) | No — anonymous function |
| Can be created inside other functions? | No | Yes |
| Can capture local variables automatically? | No | Yes (`[x]`, `[this]`, etc.) |
| Is it an object (can be passed/stored)? | No | Yes — callable object |
| Can it be stored in `std::function` or containers? | Harder | Yes, easily |
| Must it be defined at global/class scope? | Yes | No |

### Mental Model

```
void f() { ... }  
// f is the function itself.

auto f = [](){ ... };
// f is not the function — it's an object that holds an anonymous function.
```

---

## Part 5: Lambda Capabilities

### 1. Capture Variables

```cpp
int a = 10;
auto f = [a]() { return a * 2; }; // captures a
std::cout << f(); // 20
```

Impossible with normal functions.

### 2. Create Functions Dynamically

```cpp
std::vector<std::function<int(int)>> funcs;

for (int i = 1; i <= 3; ++i) {
    funcs.push_back([i](int x) { return i * x; });
}
```

Each lambda **remembers its own copy of `i`**. Normal functions cannot do this.

### 3. Inline, Short, and Passed Directly

```cpp
std::sort(vec.begin(), vec.end(),
    [](int a, int b) { return a > b; });  // no need to define a separate func
```

---

## Part 6: Alternative Implementations (Without Lambdas)

### Using std::bind

```cpp
// Without lambda (more old-style, verbose)
BaseState* CreatePausedState(StateManager* mgr) {
    return new StatePaused(mgr);
}

m_stateFactory[StateType::Paused] = std::bind(CreatePausedState, this);
```

### Using Function Pointer

```cpp
BaseState* (*fp)(StateManager*);
fp = &CreatePausedState;

m_stateFactory[StateType::Paused] = std::bind(fp, this);
```

Lambdas replace all this verbosity cleanly.

---

## Summary

### Quick Reference

| Question | Answer |
|----------|--------|
| Why do we pass `this` to `new T(this)`? | Because every State needs a pointer to the StateManager |
| Why do states need StateManager? | So they can switch states, remove states, access shared resources |
| Where does this pointer get stored? | In `BaseState* m_stateMgr` |
| Why use a lambda instead of a normal function? | Lambdas can capture `this`, be created inline, and stored in containers easily |
| What does the lambda do? | Creates a function that, when called, instantiates a new State of type T with the StateManager pointer |

### The Complete Flow

1. `RegisterState<StateGame>(StateType::Game)` is called
2. A lambda is created that captures `this` (the StateManager pointer)
3. The lambda is stored in `m_stateFactory[StateType::Game]`
4. Later, when `CreateState(StateType::Game)` is called:
   - The lambda is retrieved from the map
   - The lambda is invoked: `new StateGame(this)`
   - A new StateGame object is created with the StateManager pointer
   - The state is added to the state stack

---

## Further Reading

- [C++ Lambda Expressions (cppreference.com)](https://en.cppreference.com/w/cpp/language/lambda)
- [std::function (cppreference.com)](https://en.cppreference.com/w/cpp/utility/functional/function)
- StateManager implementation in `StateManager.hpp` and `StateManager.cpp`
