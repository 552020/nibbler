struct Point {
	x: i32,
	y: i32,
}

fn add(a: i32, b: i32) -> i32
{
	a + b
}

fn main() {
	let my_point : Point;
	// my_point.x = 3;
	// my_point.y = 7;
	
	// my_point = {2, 7}; // wrong syntax
	// my_point = Point {2, 7}; // wrong syntax - expected identifier
	my_point = Point {x: 2, y: 7};

	println!("Point x: {}: Point y: {}!", my_point.x, my_point.y);

	let sum = add(my_point.x, my_point.y);
	println!("Sum: {}", sum);

}
