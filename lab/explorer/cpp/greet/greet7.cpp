#include <iostream>
#include <string>

int main()
{
	std::string name;
	std::cout << "What's you name? ";
	std::getline(std::cin, name);
	std::cout << "Hello, " + name + "!" << std::endl;
}
