/* QUADRATIC EQUATION SOLUTION FUNCTION */

#ifndef square
#define square

#include <assert.h>
#include <float.h>
#include <math.h>

#define SS_INF_ROOTS -1     // case with infinite number of roots
#define DISC_LESS_ZERO -2   // case with two roots on a complex plane

// -------------------------------------------------------------------------------
//! Function for filtering out very small numbers
//!
// -----------------------------------------------------------------------------
int isZero(double number) {
	return fabs(number) < 0.000001;
}

// -------------------------------------------------------------------------------
//! Solves a square equation:   cf1 * x^2 + cf2 * x + cf3
//! 
//! @param [in] cf1 cf1-coefficient
//! @param [in] cf2 cf2-coefficient
//! @param [in] cf3 cf3-coefficient
//! @param [out] root1 Pointer of the 1st root
//! @param [out] root1 Pointer of the 2nd root
//!
//! return number of roots
//!
//! @note In case of infinite number of roots, returns SS_INF_ROOTS
//! @note In case of two roots on a complex plane, returns DISC_LESS_ZERO
//!
// -------------------------------------------------------------------------------
int SolveSquare(double cf1, double cf2, double cf3, double* root1, double* root2) {

	/* Check for final size */
	assert(isfinite(cf1));
	assert(isfinite(cf2));
	assert(isfinite(cf3));

	/* Checking pointers */
	assert(root1 != NULL);
	assert(root2 != NULL);
	assert(root1 != root2);

	/* Root search */
	if (isZero(cf1))
	{
		if (isZero(cf2))
		{
			return (isZero(cf3)) ? SS_INF_ROOTS : 0;
		}
		else 	// cf2 != 0
		{
			*root1 = -cf3 / cf2;
			return 1;
		}
	}
	else	// cf1 != 0		
	{
		double disc_t = cf2 * cf2 - 4 * cf1 * cf3;
		if (isZero(disc_t))
		{
			*root1 = *root2 = -cf2 / (2 * cf1);
			return 1;
		}
		else {
			if (disc_t > 0)
			{
				double sqrt_d = sqrt(disc_t);
				*root1 = (-cf2 - sqrt_d) / (2 * cf1);
				*root2 = (-cf2 + sqrt_d) / (2 * cf1);
				return 2;
			}
			else    // disc_t < 0 
			{
				return DISC_LESS_ZERO;
			}
		}
	}
}




#endif square
