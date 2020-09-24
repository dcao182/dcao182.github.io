/*************************
	Daniel Cao
	This program asks the user to input matrix data for a matrix multiplication.
*************************/
#include <iostream>
#include <iomanip>

#include "MATRIX.h"

int main() {
	Matrix obj;
	char choice = ' ';
	char loop = 'y';

	do
	{
		std::cout << "Choose one out of the four choices: " << std::endl;
		std::cout << "Enter e to input the matrix data" << std::endl;
		std::cout << "Enter c to calculate the matrix data" << std::endl;
		std::cout << "Enter d to display the input and output matrices" << std::endl;
		std::cout << "Enter q to quit the program" << std::endl;
		std::cin >> choice;

		switch (choice)
		{
		case 'e':
			obj.InputMatrix();
			std::cin.ignore();
			break;
		case 'c':
			obj.Calculate();
			std::cin.ignore();
			break;
		case 'd':
			obj.OutputMatrix();
			std::cin.ignore();
			break;
		case 'q':
			loop = 'n';
			std::cin.ignore();
			break;
		default:
			std::cout << "You entered an invalid choice.  Please try again." << std::endl;
			break;
		}
		system("PAUSE");
		system("CLS");
	} while ((loop == 'y') || (loop == 'Y'));
	return 0;
}

void Matrix::InputMatrix() {
	std::cout << "Enter how many rows and columns for matrix P: ";
	std::cin >> r1 >> c1;
	std::cout << "Enter how many rows and columns for matrix Q: ";
	std::cin >> r2 >> c2;
	std::cout << std::endl;

	std::cout << "Enter data for Matrix P: " << std::endl;
	for (int i = 0; i < r1; i++) {		// creates r1 rows
		std::cout << "Matrix p, r" << i + 1 << ": ";
		for (int j = 0; j < c1; j++) {		// creates c1 columns
			std::cin >> P[i][j];
		}
	}
	std::cout << std::endl;

	std::cout << "Enter data for Matrix Q: " << std::endl;
	for (int i = 0; i < r2; i++) {
		std::cout << "Matrix q, r" << i + 1 << ": ";
		for (int j = 0; j < c2; j++) {
			std::cin >> Q[i][j];
		}
	}
}

void Matrix::Calculate() {
	//initialize elements in array R to 0
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			R[i][j] = 0;
		}
	}

	//multiply matrices
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			for (int k = 0; k < 3; k++) {
				R[i][j] += P[i][k] * Q[k][j];
				// takes element in first row in array P multiplies with first element in first column in Q, stores in R
			}
		}
	}
}

void Matrix::OutputMatrix() {
	//format output
	std::cout << std::setw(7) << 'P' << std::setw(20) << 'Q' << std::setw(20) << 'R' << std::endl;
	std::cout << std::setw(7) << "c1" << " c2" << " c3" << std::setw(12) << "c1" << " c2" << " c3" << std::endl;
	
	for (int i = 0; i < r1; i++) {
		//displays P matrix
		std::cout << 'r' << i + 1 << "| ";
		for (int j = 0; j < c1; j++) {
			std::cout << ' ' <<  P[i][j] << ' ';
		}
		std::cout << " | " << std::setw(6);

		//displays Q matrix
		std::cout << " | ";
		for (int k = 0; k < c1; k++) {
			std::cout << ' ' << Q[i][k] << ' ';
		}

		//displays equals sign before R matrix
		if (i == 1) {
			std::cout << "| " << std::setw(3);
			std::cout << " = ";
		}
		else
			std::cout << " | " << std::setw(6);

		//displays R matrix
		std::cout << " | ";
		for (int l = 0; l < c1; l++) {
			std::cout << ' ' << R[i][l] << ' ';
		}
		std::cout << " | " << std::endl;
	}
}