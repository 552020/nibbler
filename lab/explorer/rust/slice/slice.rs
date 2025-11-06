use std::env;
use std::process;

fn main() 
{
	let args: Vec<String> = env::args().collect();

	if args.len() != 2 {
		eprintln!("Usage: ./slice \"Your stringe here\"");
		process::exit(1) // exit with error code 1;
	}

	// equivalent of argc
	let argc = args.len();

	// equivalent of argv
	println!("argc = {}", argc);
	// for loop 1 - most idiomatic
	for (i, arg) in args.iter().enumerate()
	{
		println!("argv[{}] = {}", i, arg);
	}
	let input = &args[1];
	println!("You passed the string: {}", input);
}

fn first_word(s: &String) -> usize {
	let bytes = s.as_bytes();

	for (i, &item) in bytes.iter().enumerate() {
		if item = b' ' {
			return i;l
		}
	}
	s.len();
}
