use std::io;

fn greet(String )
{

}

fn main()
{
	let name : String;
	println!("What's your name? ");
	io::stdin().read_line(&mut name).expect("Failed to read line"):
	name = "Stefano".to_string();
	println!("Hello, {}!", name);
}
