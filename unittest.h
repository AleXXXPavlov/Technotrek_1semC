/* HEADER FILE FOR UNIT TESTS */

#ifndef unittest
#define unittest

#include <stdio.h>

// -------------------------------------------------
//! Function for testing the function SolveSquare
//! 
//! @param [in] cf1 cf1-coefficient
//! @param [in] cf2 cf2-coefficient
//! @param [in] cf3 cf3-coefficient
//!
//! Either returns the location of the error 
//! or confirms the correctness of the program
// -------------------------------------------------
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

#endif unittest