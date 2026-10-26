use rand::prelude::*;
use std::cmp::Ordering;
use std::io;

fn main() {
    let correct = rand::rng().random_range(1..=100);

    println!("Yo guess the number:");

    loop {
        let mut guess = String::new();

        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line.");

        let trimmed_guess = guess.trim();

        if trimmed_guess == "quit" {
            println!("Bye!");
            break;
        }

        let num_guess: u32 = match trimmed_guess.parse() {
            Ok(num) => num,
            Err(_) => {
                println!("Please type a valid number or 'quit'!");
                continue;
            }
        };

        match num_guess.cmp(&correct) {
            Ordering::Greater => {
                println!("Lower!")
            }
            Ordering::Less => {
                println!("Higher!")
            }
            Ordering::Equal => {
                println!("Correct!");
                break;
            }
        }

        continue;
    }
}
