# C++ Interview Questions - Anki Deck

## Smart Pointers

Q: What is a `std::shared_ptr` in C++?

A: A smart pointer that maintains shared ownership of a dynamically allocated object through reference counting. The object is deleted automatically when the last `shared_ptr` pointing to it is destroyed.

___

Q: How does `std::shared_ptr` manage ownership?

A: It stores a strong reference count in a control block. Each copy of a `shared_ptr` increments the count; destruction decrements it. When the count reaches zero, the managed object is deleted.

___

Q: What is stored inside a `std::shared_ptr` object itself?

A: Usually two pointers: one to the managed object and one to the control block.

___

Q: What is the typical size of a `std::shared_ptr` on a 64-bit system?

A: 16 bytes (two 8-byte pointers).

___

Q: What information is stored in the `shared_ptr` control block?

A: The strong reference count, weak reference count, the deleter, and optional allocator information.

___

Q: Why is `make_shared` recommended over `shared_ptr<T>(new T)`?

A: Because `make_shared` allocates the object and the control block in a single memory allocation, reducing overhead and improving cache locality.

___

Q: How do reference cycles occur with `shared_ptr`?

A: When two or more objects hold `shared_ptr`s to each other, forming a loop. Their reference counts never reach zero, so they are never destroyed.

___

Q: How do you break reference cycles created by `shared_ptr`?

A: Use `std::weak_ptr` for one side of the relationship to create non-owning references.

___

## Basic Smart Pointers

Q: What are the different types of smart pointers you can declare in C++?

A: The three main types are `std::unique_ptr` (exclusive ownership), `std::shared_ptr` (shared ownership with reference counting), and `std::weak_ptr` (non-owning observer). There was also `std::auto_ptr` in C++98, but it was deprecated and removed in C++17.

___

Q: What is a smart pointer in C++?

A: A smart pointer is an object that behaves like a pointer but automatically manages the lifetime of a dynamically allocated object (usually handling deletion for you).

___

Q: Why were smart pointers introduced in modern C++?

A: To avoid memory leaks, double deletes, and other errors caused by manual use of `new` and `delete`.

___

Q: What is `std::unique_ptr`?

A: A smart pointer with exclusive ownership. Only one `unique_ptr` can own the object at a time. When it is destroyed, the object is deleted.

___

Q: What is `std::shared_ptr`?

A: A smart pointer that allows multiple owners of the same object using reference counting. The object is deleted when the last `shared_ptr` is destroyed.

___

Q: What is `std::weak_ptr`?

A: A non-owning smart pointer that observes a `shared_ptr` without increasing the reference count. It is used to break reference cycles.

___

Q: Why does `shared_ptr` use reference counting?

A: To know how many `shared_ptr`s refer to the same object and to delete the object automatically when the count reaches zero.

___

## Control Block

Q: What is the control block in a `shared_ptr`?

A: A separate internal structure allocated on the heap that stores reference counts, the deleter, and allocator info for the shared object.

___

Q: Why is it called a control block?

A: Because it *controls* the lifetime of the managed object by tracking how many `shared_ptr`s and `weak_ptr`s refer to it.

___

Q: What does the control block contain?

A: The strong reference count, weak reference count, the deleter function, and optional allocator data.

___

## Memory Size & Systems

Q: What is the typical size of a `std::shared_ptr`?

A: Usually the size of two pointers. On most systems today, that is 16 bytes.

___

Q: Why is `std::shared_ptr` usually two pointers in size?

A: One pointer is to the managed object, and the other is to the control block.

___

Q: What is a 64-bit system?

A: A computer architecture where pointers and machine words are 64 bits wide. This allows access to a much larger memory space and affects pointer sizes.

___

Q: Why does a shared_ptr take 16 bytes on a 64-bit system?

A: Because each pointer is 8 bytes on a 64-bit architecture, and shared_ptr stores two of them.

___

## Reference Cycles

Q: What is a reference cycle in C++ smart pointers?

A: A situation where two objects own each other through `shared_ptr`s, forming a loop that prevents the reference count from reaching zero.

___

Q: Why are reference cycles a problem?

A: Because the objects in the cycle will never be deleted, causing a memory leak.

___

Q: How does a `weak_ptr` help with reference cycles?

A: A `weak_ptr` does not increase the reference count. By replacing one `shared_ptr` in the cycle with a `weak_ptr`, the loop is broken and the objects can be deleted.

___

Q: Do reference cycles occur with `unique_ptr`?

A: No, because `unique_ptr` cannot be shared. It provides exclusive ownership, which cannot form cycles.

___

## Smart Pointer Declarations

Q: How do you declare a `std::unique_ptr`?

A:

```cpp
std::unique_ptr<int> p = std::make_unique<int>(5);
```

___

Q: How do you declare a `std::shared_ptr`?

A:

```cpp
std::shared_ptr<int> p = std::make_shared<int>(5);
```

___

Q: How do you declare a `std::weak_ptr`?

A:

```cpp
std::weak_ptr<int> p;        // empty weak pointer
```

___

Q: Can you assign a raw pointer directly to a smart pointer?

A: Yes, but it is unsafe. The recommended way is using `make_unique` or `make_shared` instead of `new`.

___

## Smart Pointer History

Q: When were smart pointers introduced in standard C++?

A: In C++11.

___

Q: Which smart pointers were added in C++11?

A: `std::unique_ptr`, `std::shared_ptr`, and `std::weak_ptr`.

___

Q: Was there any smart pointer before C++11?

A: C++98 had `std::auto_ptr`, but it was unsafe and removed in C++17.

___

## Type Deduction & String Literals

Q: What is the type of `auto c = "Next";` in C++?

A: `const char*`. The string literal `"Next"` is a `const char[5]` which decays to `const char*` when assigned.

___

## String Literals

Q: What is the type of the string literal `"Next"`?

A: `const char[5]`, including the terminating null character `\0`.

___

Q: Why does a string literal have type `const char[]` and not `char[]`?

A: Because modifying string literals is not allowed in C++. Adding `const` prevents accidental modification.

___

Q: Why does `"Next"` decay to a pointer?

A: Because in most expressions, arrays decay to pointers to their first element. This is a built-in language rule.

___

## Auto Deduction Rules

Q: Does `auto` keep array types?

A: No. `auto` does not preserve array types; arrays decay to pointers before auto deduces the type.

___

Q: Does `auto` keep references?

A: Only if you explicitly write `auto&` or `auto&&`. Plain `auto` removes references during deduction.

___

Q: Does `auto` keep constness of the initializer?

A: For top-level const: no.

For elements of arrays or pointers: yes.

Example: `"Next"` → `const char*` keeps the const on the pointed-to type.

___

Q: What is the type deduced by `auto x = {1,2,3};`?

A: `std::initializer_list<int>`.

___

## Array Decay

Q: What does "array decays to pointer" mean?

A: In most expressions, a C-style array becomes a pointer to its first element. Its size information is lost.

___

Q: When does an array NOT decay to a pointer?

A: When used with `sizeof`, `decltype`, reference binding, or as a function argument in templates.

___

## String Literals vs std::string

Q: Does `"Next"` create a `std::string`?

A: No. It is just a `const char[]` stored in read-only memory.

___

Q: How do you convert `"Next"` into a `std::string`?

A:

```cpp
std::string s = "Next";
```

___

Q: What is the difference between `"Next"` and `std::string("Next")`?

A: `"Next"` is a static, read-only array.

`std::string("Next")` is a dynamic, owning string object with size and capacity.

___

## Pitfalls

Q: Why is modifying a string literal undefined behavior?

A: Because it is stored in read-only memory. Attempting to write to it is illegal.


---
___

Q: What happens if you write `char* p = "Next";`?

A: It compiles (for compatibility), but modifying `*p` is undefined behavior.

___

Q: Why does `const char*` not tell you the length of the string literal?

A: Because after decay, only a pointer remains; the array size information is lost.

___