use std::{thread, time::Duration};

fn main()
{
	let mut counter = 0;

	loop {
		counter += 1;
		println!("Counter: {}", counter);
		thread::sleep(Duration::from_secs(1));
	}
}
