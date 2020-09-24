#ifndef _CHKALCK_H_
#define _CHKALCK_H_

#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<ctime>

#include "Player.h"

class ChkALck: public Player {
public:
	ChkALck(const char*, const char*, float);

	float calcPay() const;
	void print() const;
	float calcbonus();

	void choose();
	void Roll();

private:
	float bet;
	int side, roll, win, i;
	double totalwinnings;
};

#endif // _CHKALCK_H_