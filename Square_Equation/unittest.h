/* HEADER FILE FOR UNIT TESTS */

#ifndef unittest
#define unittest

#include "square.h"
#include <stdio.h>

// -------------------------------------------------
//! Function for testing one set of coefficients
//! 
//! @param [in]  pointer to the first coefficient in 
//! the array of coefficients
//! @param [in]  expected result
//! 
// -------------------------------------------------
void unitTest(double*, int);

// -------------------------------------------------
//! Function to convey parameters to a unitTest function
//!
// -------------------------------------------------
void TestSolver();

void unitTest(double* arr_cfs, int ref)
{
	double root_1, root_2;
	int res = SolveSquare(arr_cfs[0], arr_cfs[1], arr_cfs[2], &root_1, &root_2);

	if (ref == res)
	{
		printf("\nTest passed.\n");
	}
	else
	{
		printf("\nTest failed: result == %d, but should be %d.\n", ref, res);
	}
}


void TestSolver() {
	printf("\nTest run ...\n");

	/* Data for the test */
	double arr_coeff[] = { 0, 0, 0, -1, 2, 1, 23.4, -22.5745, 34, 0, 1e-4, 2.4756, 1e-10, 1e-11, 1e-10 };
	int arr_results[] = { SS_INF_ROOTS, 2, DISC_LESS_ZERO, 1, SS_INF_ROOTS };

	/* Check */
	for (int i = 0; i < 5; ++i) {
		unitTest(arr_coeff + i * 3, arr_results[i]);
	}
}

#endif unittest
