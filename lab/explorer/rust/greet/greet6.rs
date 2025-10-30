fn main()
{
	let name = String::new();
	println!("What's your name? ");
	std::io::get_line(&mut name);
	println!("Hello, {}!", name);
}
