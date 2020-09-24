#ifndef _PLAYER_H_
#define _PLAYER_H_

#include<iostream>
#include<string>
#include<cstring>
#include<iomanip>
#include<cstdlib>
#include<ctime>

class Player {
	public:
		Player(const char *, const char *);
		~Player();
		virtual float calcPay() const = 0;
		virtual void print() const;
		virtual float calcbonus() = 0;

	private:
		char *firstName, *lastName;
		float totalwinnings, bonusper;
};

#endif // _PLAYER_H_