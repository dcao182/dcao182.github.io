/*************************
	Daniel Cao
	This program inputs an entire line of text up to 132 characters into a buffer.
	It then determines how many times each letter of the alphabet occurs from a-z, A-Z and 0-9 only.
*************************/
#include <iostream>
#include <string>
#include "CHARCOUNT.h"

using namespace std;

int main() {
	char CharInput[SIZE] = {};
	int  lowerCount[26] = { 0 };
	int  upperCount[26] = { 0 };
	int  intCount[10] = { 0 };

	cout << "Please enter a sequence of characters: " << endl;
	cin.getline(CharInput, SIZE);

	CharCount(CharInput, lowerCount, upperCount, intCount);
	CountOut(lowerCount, upperCount, intCount);

	system("PAUSE");
	return 0;
}

void CharCount(char *CharInput, int *lowerCount, int *upperCount, int *intCount) {
	int i = 0;
	int x = 0;
	do {
		if (CharInput[i] >= 'a' && CharInput[i] <= 'z') {	// checks ascii of first character in input if between a & z
			x = CharInput[i] - 'a';		// subtracts ascii value of 'a' from ascii of character in input & assigns it to x
			lowerCount[x]++;	// increments count of 'a' by 1
		}
		i++;	// checks the next character in input
	} while (CharInput[i] != '\0');		// repeats until scan of input is complete

	int j = 0;
	int y = 0;
	do {
		if (CharInput[j] >= 'A' && CharInput[j] <= 'Z') {
			y = CharInput[j] - 'A';
			upperCount[y]++;
		}
		j++;
	} while (CharInput[j] != '\0');

	int k = 0;
	int z = 0;
	do {
		if (CharInput[k] >= '0' && CharInput[k] <= '9') {
			z = CharInput[k] - '0';
			intCount[z]++;
		}
		k++;
	} while (CharInput[k] != '\0');
}

void CountOut(int *lowerCount, int *upperCount, int *intCount) {
	for (char ch = 0 ; ch < 26; ch++) {
		cout << static_cast<char>(ch + 'a') << " - " << lowerCount[ch] << " times" << endl;
	}

	for (char ch = 0; ch < 26; ch++) {
		cout << static_cast<char>(ch + 'A') << " - " << upperCount[ch] << " times" << endl;
	}

	for (char ch = 0; ch < 10; ch++) {
		cout << static_cast<char>(ch + '0') << " - " << intCount[ch] << " times" << endl;
	}
}