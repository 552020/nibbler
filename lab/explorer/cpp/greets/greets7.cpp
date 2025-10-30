#include <iostream>
#include <string>

void greet(std::string name)
{
	std::cout << "Hello, " + name + " from the function!" << std::endl;
}
void greet_ref(std::string& name)
{
	std::cout << "Hello, " + name + " from the re function!" << std::endl;
}
std::string greet_ret(std::string& name)
{
	std::string msg;
	msg = "Hello, " + name + " from the ret function!";
	return msg;
}

int main()
{
	std::cout << "What's your name? ";
	std::string name;
	std::getline(std::cin, name);
	std::cout << "Hello, " + name + "!" << std::endl;
	greet(name);
	greet_ref(name);
	std::string msg;
	msg = greet_ret(name);
	std::cout << msg << std::endl;
}
