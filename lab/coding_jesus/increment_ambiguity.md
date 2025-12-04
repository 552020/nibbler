# Increment Ambiguity

This program demonstrates a C++ compilation error related to rvalues and lvalues in the context of increment operators.

## The Problem

The expression `x+++++y` fails to compile with the error:
```
error: expression is not assignable
```

## Root Cause

The issue is **not** about parsing ambiguity, but rather about **rvalue vs lvalue requirements**.

### How C++ Parses It

Due to C++'s "maximal munch" tokenization rule, `x+++++y` is parsed as:
```cpp
(x++)++ + y
```

### Why It Fails

1. **`x++` returns an rvalue**: The post-increment operator `++` returns a temporary value (rvalue), not a reference to the original variable.

2. **Increment requires an lvalue**: The increment operator `++` requires an lvalue (an assignable expression) because it needs to modify its operand.

3. **You can't increment an rvalue**: When the compiler tries to apply `++` to the result of `x++` (which is an rvalue), it fails because you cannot assign to or modify a temporary value.

### Visual Breakdown

```
x+++++y
││││││
│││││└─ y (identifier)
││││└── + (addition operator)
│││└─── ++ (post-increment - ERROR: requires lvalue, but receives rvalue!)
││└──── ++ (post-increment on x - returns rvalue)
│└───── x (identifier)
```

## The Solution

To make the code compile and work as intended, add spaces or parentheses to clarify the intent:

```cpp
std::cout << x++ + ++y;  // Post-increment x, pre-increment y, then add
```

Or more explicitly:
```cpp
std::cout << (x++) + (++y);
```

## Key Takeaway

The fundamental issue is that **increment operators require lvalues**, and **post-increment returns an rvalue**. This prevents chaining post-increment operations in a way that would require incrementing a temporary value.

