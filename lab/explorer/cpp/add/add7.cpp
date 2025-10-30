#include <iostream>

int add(int a, int b)
{
	return a + b;
}

int main()
{
	int sum = add(5, 6);
	std::cout << "Sum: " << sum << std::endl;
}
