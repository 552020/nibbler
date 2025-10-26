#include <string>
#include <iostream>

void greet_void(std::string& name)
{
	std::cout << "Hello, " + name + "!" << std::endl;
}

std::string greet(std::string& name)
{
	std::string message = "Hello, + name + "!";
	return message;
}

int main()
{
	std::string name;

	std::cout << "What's your name? ";
	std::getline(std::cin, name);
	greet_void(name);

	std::string message = greet(name);
	std::cout << message << std::endl;
	return 0;
}
