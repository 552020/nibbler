### 🦀 **Rust project structure**

Rust expects a simple but consistent layout.
You can write a single-file program or a full Cargo project.

#### **Option 1: single file**

```
main.rs
```

Compile and run manually:

```bash
rustc main.rs
./main
```

#### **Option 2: with Cargo (recommended)**

Cargo is Rust’s build & package manager (like `make` + `npm` + `pip` in one).

Create a new project:

```bash
cargo new hello_rust
cd hello_rust
```

You’ll get this structure:

```
hello_rust/
 ├─ Cargo.toml      # metadata & dependencies
 └─ src/
     └─ main.rs     # your program entry point
```

Then you run:

```bash
cargo run
```

Cargo compiles and executes automatically.

---

### 🧩 **Content of `src/main.rs`**

```rust
fn main() {
    let name = "World";
    println!("Hello, {}!", name);
}
```

---

### 🧠 **Summary of differences from C++**

| Concept        | C++                    | Rust                            |
| -------------- | ---------------------- | ------------------------------- |
| File           | `main.cpp`             | `main.rs`                       |
| Build tool     | `g++ main.cpp -o main` | `cargo run` or `rustc main.rs`  |
| Entry point    | `int main()`           | `fn main()`                     |
| Include system | `#include`             | Modules + prelude (no includes) |
| Output         | `std::cout <<`         | `println!` macro                |
