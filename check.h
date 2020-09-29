/* HEADER FILE FOR CHECK FUNCTION */

#ifndef check
#define check

#include <stdio.h>

// --------------------------------------------------------------------
//! Function for checking the correctness of the input
//! 
//! @param [in] d_num - Pointer of the n-st coefficient 
//! @param [in] prompt[] - Output information
// --------------------------------------------------------------------
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

#endif check