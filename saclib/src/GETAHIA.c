/*=======================================================================
			A <- GETAHIA(n)

Get array of hardware interval arrays.

Input
   n : a positive BETA-digit.

Output
   A : An array of n pointers to arrays of hardware intervals.
=======================================================================*/
#include <stdio.h>
#include "saclib.h"

interval **GETAHIA(n)
	BDigit (n);
{
	interval **A;

Step1: /* Allocate memory for the array. */
	A = (interval **)malloc((n) * sizeof(interval *));
	if (A == NULL)
           FAIL("GETAHIA","Out of memory.");

Return: /* Return A. */
	return(A);
}
