use std::io; // brings input/output into scope so we can use io::stdin() instead of std::io::stdin()

fn main() {
    println!("What's your name?");

    let mut name = String::new();
    io::stdin()
        .read_line(&mut name)
        .expect("Failed to read line");

    // remove the trailing newline
    let name = name.trim();

    println!("Hello, {}!", name);
}
