/* QUADRATIC EQUATION */

#include "square.h"
#include "unittest.h"
#include "check.h"

#include <stdio.h>

// --------------------------------------------------
//! Function for displaying a greeting
// --------------------------------------------------
void greeting();

// --------------------------------------------------
//! Function for displaying the result of the program
//!
//! @param [in]  pointer to the first coefficient
//! @param [in]  pointer to the second coefficient
//! @param [in]  pointer to the third coefficient
//!
// --------------------------------------------------
void result(double*, double*, double*);

int main() {

	greeting();

	double cf1 = 0, cf2 = 0, cf3 = 0;

	/* Correctness check */
	CheckDouble(&cf1, "Enter a: ");
	CheckDouble(&cf2, "Enter b: ");
	CheckDouble(&cf3, "Enter c: ");

	result(&cf1, &cf2, &cf3);

	return 0;
}

void greeting() {
	printf("# Welcome, this is square equation solver.\n# (c) Pavlov Sasha 2020 \n");
	printf("\n# Square equation: a * x^2 + b * x + c = 0\n\n");
}

void result(double* ptr1, double* ptr2, double* ptr3) {
	double root1 = 0, root2 = 0;
	int numRoots = SolveSquare(*ptr1, *ptr2, *ptr3, &root1, &root2);

	switch (numRoots)
	{
	case 0:
		printf("\nThis equation has no roots\n");
		break;

	case 1:
		printf("\nThis equation has one root.\nx = %lf\n", root1);
		break;

	case 2:
		printf("\nThis equation has two roots.\nx1 = %lf\nx2 = %lf\n", root1, root2);
		break;

	case SS_INF_ROOTS:
		printf("\nThis equation has infinitely many roots.\n");
		break;

	case DISC_LESS_ZERO:
		printf("\nThis equation has two roots in  complex plane.\n");
		break;

	default:
		printf("main(): ERROR: numRoots = %d\n", numRoots);
	}
}