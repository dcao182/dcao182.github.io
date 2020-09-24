/*************************
	Daniel Cao
	This program inputs an entire line of text up to 132 characters into a buffer.
	It then determines how many times each letter of the alphabet occurs from a-z, A-Z and 0-9 only.
*************************/
#ifndef _CHARCOUNT_H_
#define _CHARCOUNT_H_

const short SIZE = 132;

void CharCount(char *CharInput, int *lowerCount, int *upperCount, int *intCount);
void CountOut(int *lowerCount, int *upperCount, int *intCount);

#endif	/* _CHARCOUNT_H_ */