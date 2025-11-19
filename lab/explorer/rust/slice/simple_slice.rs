fn main()
{
	let str = String::from("Hello, world!");
	println!("{str}");
	// let slice = str[..];
	// println!("{slice}");
	let slice_short = str[7..=9];
	println!("{slice_short}");
	
}
