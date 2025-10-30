#include <iostream>
#include <string>

void greet_print(const std::string& name)
{
	std::cout << "Hello, " + name + "!" << std::endl;
}

std::string greet_return_message(const std::string& name)
{
	return "Hello, " + name + "!";
}
int main()
{
	std::string name;

	std::cout << "What's your name? ";
	std::getline(std::cin, name);
	greet_print(name);
}
