/* QUADRATIC EQUATION */

#include <stdio.h>
#include "square.h"

// ====================================================================

void CheckDouble(double*, const char[]); // Checking the correctness of the entered data

// ====================================================================

int main() {

	printf("# Welcome, this is square equation solver.\n# (c) Pavlov Sasha 2020 \n");
	printf("\n# Square equation: a * x^2 + b * x + c = 0\n\n");
	
	double cf1 = 0, cf2 = 0, cf3 = 0;
	
	CheckDouble(&cf1, "Enter a: ");
	CheckDouble(&cf2, "Enter b: ");
	CheckDouble(&cf3, "Enter c: ");

	double root1 = 0, root2 = 0;
	int numRoots = SolveSquare(cf1, cf2, cf3, &root1, &root2);

	switch (numRoots)
	{
	case 0:
		printf("\nThis equation hasn't roots\n");
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
		return 1;
	}

	return 0;
}

// ====================================================================

void CheckDouble(double* d_num, const char prompt[]) {
	while (1) {
		printf("%s", prompt);

		if (scanf("%lg", d_num) != 1)
		{
			printf("Input Error: Make sure that the endered data is correct.\n");

			scanf("%*[^\n]");
		}
		else
		{
			break;
		}
	}
}


