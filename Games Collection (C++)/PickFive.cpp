#include "PickFive.h"

PickFive::PickFive(const char *first, const char *last, float bee) : Player(first, last) {
	bet = bee;
}

void PickFive::choose() {
	std::cout << "Which numbers do you wish to bet on? Choose five numbers from 1 - 9: " << std::endl;
	std::cin >> num1 >> num2 >> num3 >> num4 >> num5;
	std::cout << "You bet $" << bet << " on " << num1 << ' ' << num2 << ' ' << num3 << ' ' << num4 << ' ' << num5 << "." <<  std::endl;
}

void PickFive::draw()  {
	win = 0;
	srand((unsigned)time(0));
	std::cout << "Numbers picked: " << std::endl;

	for (int i = 0; i < 5; i++) {
		p = rand() % 9 + 0;
		if (p == num1)
			win++;
		if (p == num2)
			win++;
		if (p == num3)
			win++;
		if (p == num4)
			win++;
		if (p == num5)
			win++;
		std::cout << p << std::endl;
	}
}

int PickFive::bonus() {
	if (win < 2)
		return win = 0;
	if (win == 2)
		return win = 1;
	if (win == 3)
		return win = 2;
	if (win == 4)
		return win = 3;
	if (win == 5)
		return win = 10;
}

float PickFive::calcPay() const {
	return win * bet;
}

float PickFive::calcbonus() {
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

void PickFive::print() const {
	Player::print();
}