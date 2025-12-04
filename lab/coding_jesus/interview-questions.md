# C++ Interview Questions

## Essential Topics for C++ Developer Positions

### General Position: 20-30 core questions
### Strong Position (systems, engines, finance, embedded): 50-80 topics

---

## 1. Smart Pointers (5-7 questions)

### Core Questions:
1. What is the difference between `unique_ptr`, `shared_ptr`, and `weak_ptr`?
2. What is the size of a `shared_ptr`?
3. What does a `shared_ptr` control block contain?
4. How do cycles form with `shared_ptr` and how do you break them?
5. Why does `make_shared` exist? What are its advantages?
6. When should you NOT use `shared_ptr`?
7. How do custom deleters work with smart pointers?

---

## 2. Object Lifetime & Polymorphism (8-10 questions)

### Core Questions:
1. What is the difference between dynamic type and static type?
2. Why do virtual destructors matter? What happens if you don't use them?
3. What is the meaning of `override`, `final`, and `virtual` keywords?
4. How do default arguments work with virtual functions?
5. What is object slicing and how does it occur?
6. What is RAII (Resource Acquisition Is Initialization)?
7. Explain the Rule of 0/3/5. When does each apply?
8. What happens to object lifetime when using polymorphism?
9. How does virtual function dispatch work?
10. What is the difference between early binding and late binding?

---

## 3. Value Categories & References (5-8 questions)

### Core Questions:
1. What are lvalues, rvalues, and xvalues? Give examples.
2. What are the reference collapsing rules in C++?
3. What is move semantics? How does `std::move` work?
4. What is perfect forwarding and when is it used?
5. What is copy elision? When does it occur?
6. What is the difference between `T&&` as a forwarding reference vs rvalue reference?
7. How do rvalue references enable move semantics?
8. What happens when you return a local object by value?

---

## 4. Templates & Generics (8-12 questions)

### Core Questions:
1. How does template argument deduction work?
2. What is SFINAE (Substitution Failure Is Not An Error)?
3. What is the difference between `decltype` and `auto`?
4. What are forwarding references in templates?
5. What are C++20 concepts? How do they improve templates?
6. What is CRTP (Curiously Recurring Template Pattern)?
7. How do template specialization and partial specialization work?
8. What is the difference between function templates and class templates?
9. How does `typename` differ from `class` in template parameters?
10. What is template metaprogramming?
11. How do variadic templates work?
12. What is `std::enable_if` and how is it used?

---

## 5. Memory & Performance (6-10 questions)

### Core Questions:
1. What is the difference between stack and heap memory?
2. What is memory alignment? Why does it matter?
3. How does CPU cache behavior affect performance?
4. What is small string optimization (SSO)?
5. What is memory fragmentation and how does it occur?
6. What is the size of common types (pointer, vector, shared_ptr)?
7. How does memory allocation work in C++?
8. What is the difference between `new` and `malloc`?
9. How do you detect memory leaks?
10. What is placement new and when is it used?

---

## 6. STL & Containers (8-12 questions)

### Core Questions:
1. What is the difference between `vector`, `deque`, and `list`?
2. What are iterator invalidation rules for different containers?
3. What is the difference between `map` and `unordered_map`?
4. When should you use `reserve()` on a vector?
5. What is the difference between `emplace()` and `push_back()`?
6. What is the cost of copying vs moving in containers?
7. How does `vector` grow? What is the growth factor?
8. What are the time complexities of common STL operations?
9. When should you use `array` vs `vector`?
10. How do `set` and `multiset` differ?
11. What are the iterator categories?
12. How do algorithms work with different container types?

---

## Minimal Essential Set (20 Must-Know Questions)

These are the absolute minimum for a solid C++ interview:

1. **What is the difference between `unique_ptr`, `shared_ptr`, and `weak_ptr`?**
2. **What does a `shared_ptr` control block contain?**
3. **How do memory leaks occur via cycles with `shared_ptr`?**
4. **Why do you need a virtual destructor?**
5. **What is the difference between dynamic type and static type?**
6. **What is undefined behavior? Give examples.**
7. **Explain the Rule of 3/5/0.**
8. **What is the difference between rvalue and lvalue?**
9. **How do move constructor and move assignment work?**
10. **What is copy elision?**
11. **What is const correctness?**
12. **What is the difference between references and pointers?**
13. **What is RAII?**
14. **How does STL `vector` growth behavior work?**
15. **What are iterator invalidation rules?**
16. **What is the difference between `emplace()` and `push_back()`?**
17. **What are the basics of templates?**
18. **How do `auto` and `decltype` work?**
19. **What is the difference between inheritance and composition?**
20. **How do overloaded operators work (basics)?**

---

## Additional Important Topics

### Const Correctness
- What does `const` mean in different contexts?
- What is the difference between `const` pointer and pointer to `const`?
- What is `const_cast` and when should it be used?

### Undefined Behavior
- What is undefined behavior?
- Common examples of undefined behavior
- How to avoid undefined behavior

### Exception Safety
- What are exception safety guarantees?
- What is RAII's role in exception safety?

### Lambda Expressions
- How do lambda expressions work?
- What are capture lists?
- When to use lambdas vs function objects?

### Modern C++ Features
- C++11/14/17/20 features
- Range-based for loops
- Structured bindings
- `constexpr` and `consteval`

---

## Study Checklist

- [ ] Master all 20 minimal essential questions
- [ ] Understand smart pointers deeply
- [ ] Know object lifetime and polymorphism
- [ ] Understand value categories and move semantics
- [ ] Be comfortable with templates
- [ ] Know STL containers and their characteristics
- [ ] Understand memory management
- [ ] Practice coding examples for each topic

---

## Notes

- **General C++ Developer**: Focus on the minimal essential set (20 questions)
- **Strong C++ Position**: Master all categories (50-80 topics)
- Practice explaining concepts with code examples
- Be ready to write code on the spot
- Understand not just "what" but "why" and "when"


