#ifndef _PICKFIVE_H_
#define _PICKFIVE_H_

#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<ctime>

#include "Player.h"

class PickFive: public Player {
public:
	PickFive(const char*, const char*, float);
	void choose();
	void draw();
	int bonus();
	float calcPay() const;
	float calcbonus();
	void print() const;

private:
	float bet;
	int num1, num2, num3, num4, num5, p, win, i;
	double totalwinnings;
};

#endif // _PICKFIVE_H_