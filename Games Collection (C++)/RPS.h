#ifndef _RPS_H_
#define _RPS_H_

#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<ctime>

#include "Player.h"

class RPS: public Player {
public:
	RPS(const char *, const char *, float);

	float calcPay() const;
	void print() const;
	float calcbonus();

	void rules() const;
	int choose();
	int versus();
	void result();

private:
	float bet;
	int PChoice, CChoice, win;
	double totalwinnings;
};

#endif // _RPS_H_