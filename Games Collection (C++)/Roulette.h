#ifndef _ROULETTE_H_
#define _ROULETTE_H_

#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<ctime>

#include "Player.h"

class Roulette: public Player {
public:
	Roulette(const char *, const char *, float);
	void print() const;
	float calcPay() const;
	float calcbonus();
	void game();

private:
	int number, random, typeofgame, evenodd;
	float bet;
	double totalwinnings;
};

#endif // _ROULETTE_H_