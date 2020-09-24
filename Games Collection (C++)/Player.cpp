#include "Player.h"

Player::Player(const char *first, const char *last) {
	firstName = new char[strlen(first) + 1];
	strcpy(firstName, first);
	lastName = new char[strlen(last) + 1];
	strcpy(lastName, last);
}

Player::~Player() {
	delete[] firstName;
	delete[] lastName;
}

void Player::print() const {
	std::cout << firstName << ' ' << lastName;
}