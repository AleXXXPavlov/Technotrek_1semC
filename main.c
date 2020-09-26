/* QUADRATIC EQUATION */

#include <stdio.h>
#include "square.h"
#include <Windows.h>

// ====================================================================

void CheckDouble(double*, const char[]); // Checking the correctness of the entered data
void TestSolver(); // Programm testing

// ====================================================================

int main() {
	SetConsoleOutputCP(1251);

	/* Input of initial data */
	printf("# Welcome, this is square equation solver.\n# (c) Pavlov Sasha 2020 \n");
	printf("\n# Square equation: a * x^2 + b * x + c = 0\n\n");

	double cf1 = 0, cf2 = 0, cf3 = 0;

	/* Correctness check */
	CheckDouble(&cf1, "Enter a: ");
	CheckDouble(&cf2, "Enter b: ");
	CheckDouble(&cf3, "Enter c: ");

	/* Solution implementation */
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

// ======================================================================

void TestSolver() {
	printf("\nTest run ...\n");

	/* Data for the test */
	double arr_coeff[] = { 0, 0, 0, -1, 2, 1, 23.4, -22.5745, 34, 0, 1e-7, 2.4756 };
	double arr_results[] = { SS_INF_ROOTS, 2, DISC_LESS_ZERO, 1 };
	double root1_ch = 0, root2_ch = 0;
	int check_numR;

	/* Check */
	for (int i = 0; i < 4; ++i) {
		check_numR = SolveSquare(arr_coeff[i * 3], arr_coeff[i * 3 + 1], arr_coeff[i * 3 + 2], &root1_ch, &root2_ch);

		if (check_numR == arr_results[i])
		{
			printf("\nTest №%d passed.\n", i + 1);
		}
		else
		{
			printf("\nTest №%d failed.\n", i + 1);
			printf("Final results:\n\tNumber of roots = %d\n\troot1 = %lf\n\troot2 = %lf", check_numR, &root1_ch, &root2_ch);
		}
	}
}