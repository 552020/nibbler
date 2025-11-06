fn main()
{
	format!("{:?}", (3,4)); // <-- this will throw a warning because the result is not used

	let s = String::from("Hello, world!");

	let mut s = String::new();
	s.push_str("Hello, world!");
	println!("{s}");

	let s = format!("Hello, world!");
	println!("{s}");


	let name = "Alice"; // <-- This produce a &str, a string reference
	let age = 30;

	let str = format!("Her name is {} and she is {} years old!", name, age);

	// Impossible to build using directly with String::from()

	let age_str = age.to_string(); // <-- this produce a string
	println!("age as int: {}", age);
	println!("age as str: {}", age_str);

	let str = "Her name is ".to_string() + name + ", and she is " + &age_str + " years old!"; // The first part needs to be a String. "Her name is" produces a &str (a string refrerence)

	println!("{}", str);
}
