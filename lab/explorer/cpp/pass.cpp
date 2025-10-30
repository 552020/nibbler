#include<iostream>

// 1. PASS BY VALUE 
// void f(std::string s) { }
// f(s)

// std::string f(std::string s) { }
// f(s)

void add_world_and_print(std::string str)
{
	str += ", world!";
	std::cout << str << std::endl;
}

std::string add_world_and_return(std::string str)
{
	str += ", world!";
	return str;
}

std::string to_upper(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

// 2. PASS BY REFERENCEA

void add_world_and_print_ref(std::string& str) // parameter type is std::string&, reference to a string, but we can pass into the call just std::string
{
	str += ", world";
	std::cout << str << std::endl;
}



int main()
{

	std::cout << "Hello, world!" << std::endl;

	// 1. PASS BY VALUE
	std::string hello = "Hello";
	std::cout << hello << std::endl;

	add_world_and_print(hello);
	std::cout << hello << std::endl;
	std::string hello_world = add_world_and_return(hello);
	std::cout << hello << std::endl;
	std::cout << hello_world << std::endl;

	std::string hello_lower = hello;
	hello = add_world_and_return(hello);
	std::cout << hello << std::endl;
	std::cout << hello << std::endl;

	std::string hello_upper = to_upper(hello_lower);
	std::cout << hello_upper << std::endl;
	std::cout << hello_lower << std::endl;

	// 2 PASS BY REFERENCe
	hello = "Hello";
	std::cout << hello << std::endl;
	add_world_and_print_ref(hello); // <-- str::string is passed and not std::string&
	std::cout << hello << std::endl; // <-- "Hello, world!"

	// std::string& ref = "ref"; // error: non-const lvalue reference to type 'std::string' (aka 'basic_string<char>') cannot bind to a value of unrelated type 'const char[4]' std::string& ref = "ref";
	const std::string& ref = "ref";


}
