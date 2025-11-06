fn main()
{
	let mut x = 5;
	println!("The value of x is: {x}");
	x = 6;
	println!("The value of x is: {x}");

	let x = x + 1;
	println!("The value of x after re-initialization is: {x}");
	{
		println!("The value of x in the inner scope before reassignment: {x}");
		let x = x * 2;
		println!("The value of x in the inner scope is: {x}");
	}
	println!("The value of x is: {x}");

	let x = 'a';
	println!("The value of x is: {x}");

}
