/*************************
	Daniel Cao
	This program asks the user to input matrix data for a matrix multiplication.
*************************/
#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>
#include <iomanip>

class Matrix {
	int P[20][20];
	int Q[20][20];
	int R[20][20];
	int r1, r2, r3, c1, c2, c3;
public:
	void InputMatrix();
	void Calculate();
	void OutputMatrix();
};

#endif	/* _MATRIX_H */