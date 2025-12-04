#include <iostream>
#include <memory>

int main() {
    // Create a shared pointer to an integer
    std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
    
    std::cout << "Hello, Shared Pointers!" << std::endl;
    std::cout << "Value: " << *ptr1 << std::endl;
    std::cout << "Reference count: " << ptr1.use_count() << std::endl;
    
    // Create another shared pointer that shares ownership
    std::shared_ptr<int> ptr2 = ptr1;
    
    std::cout << "\nAfter creating ptr2 (copy of ptr1):" << std::endl;
    std::cout << "ptr1 reference count: " << ptr1.use_count() << std::endl;
    std::cout << "ptr2 reference count: " << ptr2.use_count() << std::endl;
    std::cout << "Both point to the same value: " << *ptr1 << " == " << *ptr2 << std::endl;
    
    // Modify through one pointer
    *ptr2 = 100;
    std::cout << "\nAfter modifying through ptr2:" << std::endl;
    std::cout << "ptr1 value: " << *ptr1 << std::endl;
    std::cout << "ptr2 value: " << *ptr2 << std::endl;
    
    // Reset one pointer
    ptr1.reset();
    std::cout << "\nAfter resetting ptr1:" << std::endl;
    std::cout << "ptr1 is null: " << (ptr1 == nullptr) << std::endl;
    std::cout << "ptr2 reference count: " << ptr2.use_count() << std::endl;
    std::cout << "ptr2 value: " << *ptr2 << std::endl;
    
    // When ptr2 goes out of scope, the memory is automatically freed
    std::cout << "\nProgram ending - shared pointer will automatically clean up!" << std::endl;
    
    return 0;
}

