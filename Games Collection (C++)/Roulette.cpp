#include "Roulette.h"

Roulette::Roulette (const char *first, const char *last, float b) : Player(first, last) {
	bet = b;
}

void Roulette::game() {
	srand((unsigned)time(0));

	std::cout << "Please select what you're betting on: " << std::endl;
	std::cout << "1 = Bet on a specific number (1 - 37), 2 = Bet on even or odd: ";
	std::cin >> typeofgame;
    
	if (typeofgame == 1) {
		std::cout << "What number would you like to bet on? ";
		std::cin >> number;
		std::cout << "You bet $" << bet << " on " << number << "." << std::endl;
		random = rand() % 37 + 1; 
		std::cout << "The wheel came up " << random << "." << std::endl;
		if (number != random) {
			std::cout << "You lose $" << bet << "." << std::endl;
			totalwinnings -= bet;
		} else {
			std::cout << "You win $" << 35*bet << "." << std::endl;
			totalwinnings += 35*bet;
		}
	}
	if (typeofgame == 2) {
		std::cout << "Are you betting on even (1) or odd (2)? ";
		std::cin >> evenodd;
		random = rand()%37;
		std::cout << "The wheel came up " << random << "." << std::endl;
		if (evenodd == 1) {
			if(2 * (random / 2) == random) {
				std::cout << "You win $" << bet << "." << std::endl;
				totalwinnings += bet;
			} else {
				std::cout << "You lose $" << bet << "." << std::endl;
				totalwinnings -= bet;
			}
		}
		if (evenodd == 2) {
			if (2 * (random / 2) == random) {
				std::cout << "You lose $" << bet << "." << std::endl;
				totalwinnings -= bet;
			} else {
				std::cout << "You win $" << bet << "." << std::endl;
				totalwinnings += bet;
			}
		}
	}
}

float Roulette::calcPay() const { 
	if (totalwinnings <= 0)
		return 0;
	else
		return totalwinnings;
}

float Roulette::calcbonus() {
	totalwinnings = calcPay();

	if (totalwinnings <= 0)
		totalwinnings = 0;

	if (totalwinnings > 0 && totalwinnings <= 10)
		totalwinnings += (totalwinnings * .012);

	if (totalwinnings > 10 && totalwinnings <= 100)
		totalwinnings += (totalwinnings * .016);

	if (totalwinnings > 100 && totalwinnings <= 500)
		totalwinnings += (totalwinnings * .021);

	if (totalwinnings > 500)
		totalwinnings += (totalwinnings * .035);

	return totalwinnings;
}

void Roulette::print() const {
	Player::print();
}