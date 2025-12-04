# BaseState and StateManager Interdependency

## Overview

Currently, `BaseState` holds a reference to `StateManager`, creating bidirectional coupling between the state interface and the state manager. This interdependency complicates the architecture and makes it harder to reason about the relationship between classes.

## Current Design

**BaseState** holds `StateManager* m_stateMgr` and uses it for:
1. **State transitions**: `m_stateMgr->SwitchTo(StateType::MainMenu)`
2. **Accessing shared resources**: `m_stateMgr->GetContext()->m_wind`
3. **State removal**: `m_stateMgr->Remove(StateType::Intro)`

**StateManager** is a `friend` of `BaseState` to call lifecycle methods:
- `OnCreate()`, `OnDestroy()`, `Activate()`, `Deactivate()`

## Problem

**Interdependency creates complexity:**
- States depend on StateManager (for transitions and resources)
- StateManager depends on BaseState (to manage lifecycle)
- This circular dependency makes the architecture harder to understand
- States are not truly independent - they're tightly coupled to the manager

**Why this matters:**
- Harder to reason about code flow
- States can't exist independently
- Testing states requires mocking StateManager
- Changes to StateManager interface affect all states
- Violates single responsibility principle (states manage themselves AND request transitions)

## Alternative Designs

### Option 1: Direct SharedContext in BaseState

```cpp
class BaseState {
protected:
    SharedContext* m_context;  // Direct access, no StateManager needed
};
```

**Pros:**
- States can access resources without StateManager
- Reduces one dependency

**Cons:**
- Still need a way to request state transitions
- States still coupled to the state system

### Option 2: Event-Based State Transitions

States emit transition events instead of calling StateManager directly:

```cpp
class BaseState {
protected:
    SharedContext* m_context;
    // Emit transition request instead of calling StateManager
    void RequestTransition(StateType nextState);
};
```

StateManager listens to transition events and performs the switch.

**Pros:**
- States don't need StateManager reference
- Decouples transition logic
- More flexible (multiple listeners possible)

**Cons:**
- Requires event system
- Slightly more complex

### Option 3: Return-Based Transitions

States return transition requests from Update():

```cpp
enum class TransitionRequest {
    None,
    SwitchTo(StateType),
    Remove(StateType),
    Push(StateType)
};

class BaseState {
    virtual TransitionRequest Update(const sf::Time& l_time) = 0;
};
```

StateManager checks return value and acts accordingly.

**Pros:**
- No StateManager reference needed
- Clear, explicit transition model
- States are completely independent

**Cons:**
- Only one transition per Update() call
- Less reactive (can't transition immediately on event)

### Option 4: Dependency Injection Pattern

Pass only what states need, not the entire StateManager:

```cpp
class BaseState {
protected:
    SharedContext* m_context;
    StateTransitionInterface* m_transitions;  // Interface, not full StateManager
};
```

**Pros:**
- States only depend on what they use
- Can mock transition interface for testing
- Clearer dependencies

**Cons:**
- Still some coupling
- Need to define transition interface

## Recommended Approach

**Hybrid: Direct SharedContext + Event-Based Transitions**

1. BaseState holds `SharedContext*` directly (no StateManager needed for resources)
2. States emit transition events (no direct StateManager calls)
3. StateManager listens to events and manages transitions
4. Remove `friend` declaration - StateManager can call public lifecycle methods

**Benefits:**
- BaseState becomes independent
- Clear separation of concerns
- Easier to test and reason about
- States are self-contained

## Todo

- [ ] Analyze current usage patterns (how often do states call StateManager?)
- [ ] Design event system for state transitions (if going with event-based approach)
- [ ] Refactor BaseState to hold SharedContext directly
- [ ] Remove StateManager reference from BaseState
- [ ] Implement transition event system
- [ ] Update all state implementations to use new pattern
- [ ] Remove `friend` declaration if no longer needed
- [ ] Test that all state transitions still work correctly
- [ ] Document the new architecture

## Notes

This refactoring is **not essential** for functionality, but would improve:
- Code clarity
- Testability
- Maintainability
- Understanding of class relationships

Consider this a **code quality improvement** rather than a bug fix.

Short answer:
You’re seeing a real design trade-off, not a “bug”. Your write-up is good, but for this scale of project I’d treat it as “nice refactor later”, not something to fix now.

Let me react point-by-point, but compact.

---

1. Is this actually “bad” design?

In classic State pattern, each State usually holds a pointer to the “Context” (here: StateManager or some thinner interface). So

* StateManager → BaseState (polymorphism)
* BaseState → StateManager (to request transitions, access shared stuff)

is very common.

It’s not a *compile-time* circular dependency (headers can be organized with forward declarations), it’s just a **runtime bidirectional relationship**. That’s OK as long as roles are clear:

* StateManager owns states, drives their lifecycle.
* States own their local logic and can ask for transitions.

So: yes, it’s coupling, but it’s also normal for this pattern.

---

2. Your concerns are real, but mostly architectural:

You’re right about:

* Harder testing (you need at least a fake StateManager).
* States knowing “too much” (they can call SwitchTo, Remove, etc).
* BaseState being a bit “heavy” (life cycle + transition logic).

These are real **code quality** points, not functional problems.

---

3. Quick thoughts on your options

Very condensed:

* Option 1: BaseState only has SharedContext
  Good for removing the “resource” dependency on StateManager, but you still need some way to request transitions → you’ll invent something else anyway.

* Option 2: Event-based transitions
  Clean, decoupled, but: you now need an event bus + more plumbing. Great for a bigger engine, overkill for “Snake + few menus”.

* Option 3: Return-based transitions from Update
  Conceptually nice (pure states, no manager pointer). Downsides:

  * You have to encode all transitions into a small enum / struct.
  * Only one transition per Update unless you make it more complex.
  * You push transition handling logic into StateManager’s post-Update step.

* Option 4: Inject narrow interface (StateTransitionInterface)
  This is the sweet spot if you want to clean it up without going crazy:

  * BaseState depends on:

    * SharedContext* (for window / resources)
    * StateTransitions* (with methods like SwitchTo, Remove, Push)
  * Implementation: StateManager implements StateTransitions.
  * Tests: you can pass a fake transitions object.

This keeps the current behavior but **shrinks** the dependency.

---

4. What I’d recommend for you, concretely

Given where you are:

* You’re still implementing the book’s code.
* You already have a *lot* of moving parts (event system, states, Nibbler, SFML vs SDL vs raylib).

I’d do this:

1. Don’t refactor the architecture yet. Keep `BaseState` holding `StateManager*`.
2. Mentally note: “In a bigger engine I’d:

   * give BaseState a SharedContext pointer directly
   * and a small StateTransitions interface instead of full StateManager.”
3. If you really want one improvement now with minimal breakage:
   change `BaseState` to store:

   ```cpp
   struct IStateTransitions {
       virtual void SwitchTo(StateType) = 0;
       virtual void Remove(StateType)   = 0;
       virtual void Push(StateType)     = 0;
       virtual ~IStateTransitions() = default;
   };
   ```

   and have `StateManager` implement that.
   Then BaseState only knows `IStateTransitions` + `SharedContext`.

That gives you the “architectural correctness” you want, without introducing an event bus and without rewriting the book.

---

5. Bottom line

* Your analysis is solid; you’re thinking like an engine designer.
* For this SFML book project, the current coupling is acceptable and common.
* If you want to polish it, the dependency-injection pattern (Option 4) is the best cost/benefit right now.
* Event-based transitions (Option 2) are nice, but that’s a **whole extra subsystem** you then have to maintain and understand.

If you want, we can sketch the exact diff you’d need to implement Option 4 (interfaces + constructor changes) without breaking everything.
