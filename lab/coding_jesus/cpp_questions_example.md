Q: What is the difference between unique_ptr, shared_ptr, and weak_ptr?

A: 
- **unique_ptr**: Exclusive ownership, cannot be copied, only moved. Automatically deletes the object when it goes out of scope.
- **shared_ptr**: Shared ownership with reference counting. Multiple shared_ptr instances can point to the same object. Object is deleted when the last shared_ptr is destroyed.
- **weak_ptr**: Non-owning observer pointer. Doesn't affect reference count. Used to break cycles and check if object still exists.

Q: What is the size of a shared_ptr?

A: Typically 16 bytes on 64-bit systems: 8 bytes for the pointer to the object, and 8 bytes for the pointer to the control block (which contains the reference count and deleter).

Q: What does a shared_ptr control block contain?

A: The control block contains:
- Reference count (for shared_ptr)
- Weak reference count (for weak_ptr)
- Custom deleter (if provided)
- Allocator (if custom allocator is used)

Q: How do cycles form with shared_ptr and how do you break them?

A: Cycles form when objects reference each other through shared_ptr, creating a circular dependency. For example, A has a shared_ptr to B, and B has a shared_ptr to A. This prevents automatic deletion. Break cycles by using weak_ptr for one of the references, as weak_ptr doesn't affect the reference count.

Q: Why does make_shared exist? What are its advantages?

A: `make_shared` allocates both the object and the control block in a single memory allocation, which is more efficient than separate allocations. It also provides exception safety and reduces memory fragmentation.

Q: When should you NOT use shared_ptr?

A: Don't use shared_ptr when:
- You need exclusive ownership (use unique_ptr)
- You have a single owner (use unique_ptr)
- You need to break cycles (use weak_ptr for one side)
- Performance is critical (shared_ptr has overhead)
- You're in a tight loop or real-time system

Q: What is the difference between dynamic type and static type?

A: 
- **Static type**: The type known at compile time (the declared type)
- **Dynamic type**: The actual type of the object at runtime (the most derived type)

Example: `Base* p = new Derived();` - static type is `Base*`, dynamic type is `Derived*`.

Q: Why do virtual destructors matter? What happens if you don't use them?

A: Virtual destructors ensure that when you delete an object through a base class pointer, the derived class destructor is called. Without a virtual destructor, only the base class destructor runs, leading to undefined behavior and potential memory leaks.

Q: What is RAII (Resource Acquisition Is Initialization)?

A: RAII is a C++ programming technique where resources (memory, file handles, locks) are tied to object lifetime. Resources are acquired in the constructor and released in the destructor, ensuring automatic cleanup even if exceptions occur.

Q: Explain the Rule of 0/3/5. When does each apply?

A: 
- **Rule of 0**: Don't define any of the special member functions (destructor, copy constructor, copy assignment). Let the compiler generate them.
- **Rule of 3**: If you define one of destructor, copy constructor, or copy assignment, you should define all three.
- **Rule of 5**: With C++11, add move constructor and move assignment to the Rule of 3, making it Rule of 5.

Q: What are lvalues, rvalues, and xvalues? Give examples.

A: 
- **lvalue**: An expression that refers to a memory location (can appear on left side of assignment). Example: `int x = 5;` - `x` is an lvalue.
- **rvalue**: A temporary value that doesn't have a memory location. Example: `5`, `x + 1`, function return by value.
- **xvalue**: An "expiring value" - an lvalue that can be moved from. Example: Result of `std::move(x)`.

Q: What is move semantics? How does std::move work?

A: Move semantics allows transferring ownership of resources from one object to another without copying. `std::move` is a cast that converts an lvalue to an rvalue reference, enabling move constructors and move assignment operators to be called. It doesn't actually move anything - it just enables the move.

Q: What is copy elision? When does it occur?

A: Copy elision is a compiler optimization that eliminates unnecessary copy or move operations. It occurs in:
- Return value optimization (RVO)
- Named return value optimization (NRVO)
- When initializing objects from temporaries

Q: What is the difference between stack and heap memory?

A: 
- **Stack**: Fast, automatic allocation/deallocation, limited size, local to function scope
- **Heap**: Slower, manual allocation/deallocation (or smart pointers), larger size, persists beyond function scope

Q: What is the difference between vector, deque, and list?

A: 
- **vector**: Dynamic array, contiguous memory, fast random access, slow insertions in middle
- **deque**: Double-ended queue, segmented memory, fast insertions at both ends, slower random access than vector
- **list**: Doubly-linked list, non-contiguous, fast insertions/deletions anywhere, no random access

Q: What are iterator invalidation rules for different containers?

A: 
- **vector**: Invalidated on reallocation (push_back, insert when capacity exceeded)
- **deque**: Invalidated when insertion/deletion in middle, but not at ends
- **list**: Never invalidated (unless element is deleted)
- **map/unordered_map**: Invalidated when element is deleted

Q: What is the difference between emplace() and push_back()?

A: `emplace()` constructs the object directly in the container using the provided arguments, avoiding a copy or move. `push_back()` requires the object to already exist (or be constructed from arguments), potentially causing an extra copy/move operation.

