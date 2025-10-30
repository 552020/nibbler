use std::io;

// Greet takes a reference to a string and print a message
fn greet(name; &str) --> String 
{
	println("Hello, {}!", name);
}

fn greet_explicit(name: &str) --> String
{
	let mut message = String::new();
	// message = println("Hello, {}!", name); // wrong
	message = format!("Hello, {}!", name);
	return message;
}

fn main()
{

 // 1. Method
	println!("What's your name? ");
	let mut name = String::new(); // <-- owned, growable string stored on the heap // inferred: String
	// let mut name : String = String::new() // <-- 
	std::io::stdin().read_line(&mut name).expect("Failed to read line");
	let name = name.trim();
	println!("Hello {}!", name);

	// 2. Method
	println!("What's your name again? ");
	let mut name = String::new();
	std::io::stdin().read_line(&mut name).expect("Failed to read line");
	let name = name.trim(); // <-- here name becomes &str // .trim() returns a string slice - a reference pointing inside th String
	// let name : &str = name.trim();
	let message = greet_explicit(name);
	println!("{}", message);
	// 3 Method

}
