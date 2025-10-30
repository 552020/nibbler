use std::io;

fn main()
{
	let mut name : String = String.new();
	println!("What's your name? ");
	io::stdin().readline(&mut name).expect("Failed to read line");
	let name = name.trim();
	println!("Hello, {}!", name).expect("Failed to read line");
}
