#include <iostream>
#include <string>

struct Point
{
	int x;
	int y;
	};


int main()
{

	std::string name;
	Point my_point;
	//	my_point.x = 3;
	// my_point.y = 7;
	std::cout << "Point x: "  << my_point.x << "; Point y: " << my_point.y << "!" << std::endl;

	return 0;
}
