#include <iostream> 
#include <string>

void greet(std::string &name)
{
	std::cout << "Hello, " + name + "!" << std::endl;
}

std::string greet_return_message(std::string &name)
{
	std::string message = "Hello, " + name + "!";
	return message;
}

int main()
{
	std::string name;
	std::cout << "What's your name? ";
	std::getline(std::cin, name);
	std::cout << "Hello, " + name + "!" << std::endl;
	std::string message;
	message = greet_return_message(name);
	std::cout << message << std::endl;
	greet(name);
}
