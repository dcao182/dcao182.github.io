#include<iostream>  // input, output
#include<string>    // required for strings
#include<iomanip>  // required for parametric modifiers, setprecision
#include<cstdlib> // required for math functions
#include<ctime> // required for timer

#include "Player.h"
#include "PickFive.h"
#include "ChkALck.h"
#include "Roulette.h"
#include "RPS.h"

int main() {
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << "Welcome to the Casino!" << std::endl << std::endl;
    
	// PICK 5

	std::cout << "LET'S PLAY PICK 5!" << std::endl << std::endl;
	PickFive playerPF ("This", "loser", 10.0);
	playerPF.choose();
	playerPF.draw();
	playerPF.bonus();
	playerPF.print();
	std::cout << " won $" << playerPF.calcPay() << "." << std::endl;
	std::cout << "With the casino bonus, "; 
	playerPF.print();
	std::cout << " won a total of $" << playerPF.calcbonus() << "." << std::endl << std::endl;

	// CHUCK-A-LUCK

	std::cout << "LET'S PLAY CHUCK-A-LUCK!" << std::endl << std::endl;

	ChkALck playerCAL ("This", "loser", 10.0);
	playerCAL.choose();
	playerCAL.Roll();
	playerCAL.print();
	std::cout << " won $" << playerCAL.calcPay() << "." << std::endl;
	std::cout << "With the casino bonus, "; 
	playerCAL.print();
	std::cout << " won a total of $" << playerCAL.calcbonus() << "." << std::endl << std::endl;

	// ROULETTE

	std::cout << "LET'S PLAY ROULETTE!" << std::endl << std::endl;
	Roulette playerR ("This", "Loser", 10.0);
	playerR.game();
	playerR.print();
	std::cout << " won $" << playerR.calcPay() << "." << std::endl;
	std::cout << "With the casino bonus, "; 
	playerR.print();
	std::cout << " won a total of $" << playerR.calcbonus() << "." << std::endl << std::endl;

	// ROCK, PAPER, SCISSORS, LIZARD, SPOCK

	std::cout << "LET'S PLAY ROCK, PAPER, SCISSORS, LIZARD, SPOCK!" << std::endl << std::endl;

	RPS playerRPS ("This", "Loser", 15.0);
	playerRPS.rules();
	for (int i = 0; i < 3; i++) {
		playerRPS.choose();
		playerRPS.versus();
		playerRPS.result();
	}
	playerRPS.print();
	std::cout << " won $" << playerRPS.calcPay() << "." << std::endl;
	std::cout << "With the casino bonus, "; 
	playerRPS.print();
	std::cout << " won a total of $" << playerRPS.calcbonus() << "." << std:: endl << std::endl;

	std::cout << "Thank you for playing!!" << std::endl << std::endl;

	system("PAUSE");
	return 0;
}

/*
welcome to the Casino!

LET'S PLAY PICK 5!

which numbers do you wish to bet on? Choose five numbers from 1 - 9: 
4
1
3
9
7
You bet $10.00 on 4 1 3 9 7
You picked:
0
7
5
7
5
This loser won $10.00
With the casino bonus, This loser won a total of $10.28

LET'S PLAY CHUCK-A-LUCK!

which side of a die do you wish to bet on?
4
you bet $10.00 on 4

you rolled:
6
5
1
6
5
This loser won $0.00
With the casino bonus, This loser won a total of $0.00

LET'S PLAY ROULETTE!

Please select what you're betting on:
1 = Bet on a specific number (1 - 37), 2 = Bet on even or odd   1
What number would you like to bet on? 32
bet $10.00 on 32
The wheel came up 18
You lose $10.00
This Loser won $0.00
With the casino bonus, This Loser won a total of $0.00

LET'S PLAY ROCK, PAPER, SCISSORS, LIZARD, SPOCK!

Here are the rules:
Scissors beat Paper and Lizard
Paper beats Rock and Spock
Rock beats Scissors and Lizard
Lizard beats Spock and Paper
Spock beats Scissors and Rock

You will play three times against a computer.

Please choose your choice:
1 = Rock, 2 = Paper, 3 = Scissors, 4 = Lizard, 5 = Spock        4

 Player Chooses: Lizard
 Computer Chooses: Paper

 Congratulations, You WON!

Please choose your choice:
1 = Rock, 2 = Paper, 3 = Scissors, 4 = Lizard, 5 = Spock        3

 Player Chooses: Scissors
 Computer Chooses: Scissors

 It's a TIE!

Please choose your choice:
1 = Rock, 2 = Paper, 3 = Scissors, 4 = Lizard, 5 = Spock        5

 Player Chooses: Spock
 Computer Chooses: Scissors

 Congratulations, You WON!

This Loser won $30.00
With the casino bonus, This Loser won a total of $30.48

Thank you for playing!!

Press any key to continue . . .

*/