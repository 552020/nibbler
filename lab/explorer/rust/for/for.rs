fn main()
{
	// NORMAL
	for i in 0..5 {
		println!("{}", i);
	}
	// OVER ARRAY
	let arr = [10, 20, 30];
	for value in arr {
		println!("{}", value);
	}
	// WITH INDEX
	for (index, value) in arr.iter().enumerate()
	{
		println!("{}: {}", index, value);
	}
}
