#include <iostream>
#include <string>

std::string greet(const std::string &name)
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
	
	// std::cout << "Hello World!" << std::endl;
}
