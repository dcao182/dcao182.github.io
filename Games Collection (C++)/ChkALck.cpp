#include "ChkALck.h"

ChkALck::ChkALck(const char *first, const char *last, float b) : Player(first, last) {
	bet = b;
}

void ChkALck::choose() {
	std::cout << "which side of a die do you wish to bet on? " << std::endl;
	std::cin >> side;
	std::cout << "You bet $" << bet << " on " << side << "." << std::endl << std::endl;
}

void ChkALck::Roll() {
	win = 0;
	srand((unsigned)time(0));
	std::cout << "You rolled: " << std::endl;

	for (i = 0; i < 5; i++)
	{
	roll = rand() % 6 + 1;
	if (roll == side)
		win++;
	std::cout << roll << std::endl;
	}
}

float ChkALck::calcPay() const {
	return win * bet;
}

float ChkALck::calcbonus() {
	totalwinnings = calcPay();

	if (totalwinnings == 0)
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

void ChkALck::print() const {
	Player::print();
}