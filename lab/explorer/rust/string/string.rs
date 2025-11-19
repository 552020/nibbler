fn main()
{
	println!("Hello, world!");

	let s1 = String::from("hello"); // "hello" is in Rust a &str
	println!("{s1}");

	let s2 = "Café à 5€".to_string();
	println!("{s2}");

	let s3: String = "hello".into();
	println!("{s3}");

	let mut s4 = String::new();
	s4.push_str("hello");
	println!("{s4}");

	println!("bytes s1 = {}", s1.len());
	println!("chars s1 = {}", s1.chars().count());
	println!();
	println!("bytes s2 = {}", s2.len());
	println!("chars s2 = {}", s2.chars().count());
	println!();

	
}
