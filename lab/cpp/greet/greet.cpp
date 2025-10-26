#include <iostream>  // For std::cout, std::cin, std::endl (input/output operations)
#include <string>    // For std::string data type and string operations

std::string greet(const std::string& name)
{
	return "Hello, " + name + "!";
}

int main()
{
	std::string name;

	std::cout << "What's your name? ";
	std::getline(std::cin, name);

	std::string message = greet(name);
	std::cout << message << std::endl;

	return 0;
}
