#include "RPS.h"

RPS::RPS(const char *first, const char *last, float b) : Player(first, last) {
	bet = b;
	win = 0;
}

void RPS::rules() const {
	std::cout << "Here are the rules: " << std::endl;
	std::cout << "Scissors beat Paper and Lizard." << std::endl;
	std::cout << "Paper beats Rock and Spock." << std::endl;
	std::cout << "Rock beats Scissors and Lizard." << std::endl;
	std::cout << "Lizard beats Spock and Paper." << std::endl;
	std::cout << "Spock beats Scissors and Rock." << std::endl << std::endl;
	std::cout << "You will play three times against a computer." << std::endl << std::endl;
}

int RPS::choose() {
	std::cout << "Please choose your choice: " << std::endl;
	std::cout << "1 = Rock, 2 = Paper, 3 = Scissors, 4 = Lizard, 5 = Spock	";
	std::cin >> PChoice;
	std::cout << std::endl;
	if ( PChoice == 1 ) {
        std::cout <<" Player Chooses: Rock " << std::endl;
    } else if ( PChoice == 2 ) {
        std::cout <<" Player Chooses: Paper " << std::endl;
    } else if (PChoice == 3) { 
        std::cout <<" Player Chooses: Scissors " << std::endl;
    } else if (PChoice == 4) {
        std::cout << " Player Chooses: Lizard " << std::endl;
    } else if (PChoice == 5) {
        std::cout << " Player Chooses: Spock " << std::endl;
        return PChoice;
    }
}

int RPS::versus() {
	srand((unsigned)time(0));
    CChoice = rand() % 5 + 1;
    
    if ( CChoice == 1 ) {
        std::cout << " Computer Chooses: Rock " << std::endl << std::endl;
    } else if ( CChoice == 2 ) {
        std::cout << " Computer Chooses: Paper " << std::endl << std::endl;
    } else if ( CChoice == 3 ) {
        std::cout << " Computer Chooses: Scissors " << std::endl << std::endl;
    } else if ( CChoice == 4 ) {
        std::cout << " Computer Chooses: Lizard " << std::endl << std::endl;
    } else if ( CChoice == 5 ) {
        std::cout << " Computer Chooses: Spock " << std::endl << std::endl;
        return CChoice;
    }
}

void RPS::result() {
	if ( ( PChoice == 1 && CChoice == 1 ) ||
        ( PChoice == 2 && CChoice == 2 ) ||
        ( PChoice == 3 && CChoice == 3 ) ||
        ( PChoice == 4 && CChoice == 4 ) ||
        ( PChoice == 5 && CChoice == 5 ) ) {
        std::cout << " It's a TIE! " << std::endl << std::endl;
    } else if (( PChoice == 3 && CChoice == 2 ) ||
             ( PChoice == 2 && CChoice == 1 ) ||
             ( PChoice == 1 && CChoice == 4 ) ||
             ( PChoice == 4 && CChoice == 5 ) ||
             ( PChoice == 5 && CChoice == 3 ) ||
             ( PChoice == 3 && CChoice == 4 ) ||
             ( PChoice == 4 && CChoice == 2 ) ||
             ( PChoice == 2 && CChoice == 5 ) ||
             ( PChoice == 5 && CChoice == 1 ) ||
             ( PChoice == 1 && CChoice == 3 )) {
        std::cout << " Congratulations, You WON! " << std::endl << std::endl;
		win++;
    } else if (( PChoice == 2 && CChoice == 3 ) ||
             ( PChoice == 1 && CChoice == 2 ) ||
             ( PChoice == 4 && CChoice == 1 ) ||
             ( PChoice == 5 && CChoice == 4 ) ||
             ( PChoice == 3 && CChoice == 5 ) ||
             ( PChoice == 4 && CChoice == 3 ) ||
             ( PChoice == 2 && CChoice == 4 ) ||
             ( PChoice == 5 && CChoice == 2 ) ||
             ( PChoice == 1 && CChoice == 5 ) ||
             ( PChoice == 3 && CChoice == 1 )) {
        std::cout << " You Lost! " << std::endl << std::endl; 
    }
}

float RPS::calcPay() const {
	return win * bet;
}

float RPS::calcbonus() {
	totalwinnings = calcPay();

	if(totalwinnings == 0)
		totalwinnings = 0;

	if(totalwinnings > 0 && totalwinnings <= 10)
		totalwinnings += (totalwinnings * .012);

	if(totalwinnings > 10 && totalwinnings <= 100)
		totalwinnings += (totalwinnings * .016);

	if(totalwinnings > 100 && totalwinnings <= 500)
		totalwinnings += (totalwinnings * .021);

	if(totalwinnings > 500)
		totalwinnings += (totalwinnings * .035);

	return totalwinnings;
}

void RPS::print() const {
	Player::print();
}