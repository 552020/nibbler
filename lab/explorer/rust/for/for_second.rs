fn main()
{
	println!("1. for over array by value (IntoIterator) - with Sugar");
	let a = [1, 2, 3, 4, 5];
	for element in a {
		// element: i32 (copied)
		println("[value] element = {element}");
	}

	println!("2. for over array by value (IntoIterator) - with no Sugar");
	let a = [1, 2, 3, 4, 5];
	// for element in a {
	for element in IntoIterator::into_iter(a) {
		// element: i32 (copied)
		println("[value] element = {element}");
	}
	
	println!("1. for over array by value (IntoIterator)");
	let b = [1, 2, 3, 4, 5];
	for element_ref in b.iter() {
		// element_ref: &i32
		println!("[iter] element_ref = {element_ref}");
	}

	println!("4. enumerate but copy out the value (deref) ");
	let d = [1, 2, 3, 4, 5];
	for (i, element_ref) in d.iter().enumerate {
		// element_ref: &i32
		println!("[iter] element_ref = {element_ref}");
}
