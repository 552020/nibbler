#include <iostream>
#include <string>

struct Point
{
	int x;
	int y;
};


int add(int a, int b)
{
	return a + b;
}


int main()
{

	std::string name;
	Point my_point;
	// my_point.x = 3;
	// my_point.y = 7;

	int sum;
	sum = add(my_point.x, my_point.y);

	std::cout << "Point x: "  << my_point.x << "; Point y: " << my_point.y << "!" << std::endl;
	std::cout << "Sum: " << sum << std::endl;

	return 0;
}
