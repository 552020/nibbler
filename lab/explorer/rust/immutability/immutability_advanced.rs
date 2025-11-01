struct Point {
    x: i32,
    y: i32,
}

fn main() {
    // immutable binding → whole value is frozen
    let _p = Point { x: 1, y: 2 };
    // _p.x = 10;              // ❌ cannot assign to field of immutable binding

    // mutable binding → whole value can change
    let mut q = Point { x: 3, y: 4 };
    q.x = 30;                  // ✅

    // immutable borrow
    let _r: &Point = &q;
    // _r.x = 99;               // ❌ cannot modify through &T

    // mutable borrow
    let r_mut: &mut Point = &mut q;
    r_mut.x = 50;              // ✅

    // if you want C++-style "interior mutability", you must opt in:
    use std::cell::Cell;
    struct Wrap {
        inner: Cell<i32>,
    }
    let w = Wrap { inner: Cell::new(10) };
    // w is not mut, but inner can change:
    w.inner.set(42);           // ✅ interior mutability

    println!("q = ({}, {})", q.x, q.y);
    println!("w.inner = {}", w.inner.get());
}

