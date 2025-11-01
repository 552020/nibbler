#include <iostream>

struct Point {
    int x;
    int y;
};

int main() {
    Point p{1, 2};

    // 1) pointer to const data (you can't change *p1, but you can move p1)
    const Point* p1 = &p;
    // p1->x = 10;        // ❌ error: data is const
    p1 = nullptr;          // ✅ pointer itself is movable

    // 2) const pointer to mutable data (you can change *p2, but not p2)
    Point* const p2 = &p;
    p2->x = 20;            // ✅ ok: data is mutable
    // p2 = nullptr;       // ❌ error: pointer is const

    // 3) const pointer to const data (neither)
    const Point* const p3 = &p;
    // p3->x = 30;         // ❌ cannot modify data
    // p3 = nullptr;       // ❌ cannot reassign pointer

    std::cout << "p = (" << p.x << ", " << p.y << ")\n";
    return 0;
}

