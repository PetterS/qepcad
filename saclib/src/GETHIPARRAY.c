/*==========================================================================
                              A <- GETHIPARRAY(n)

Get hardware interval polynomial array.

Input
   n : a BETA-digit, n >= 0.

Output
   A : a pointer to an array of n + 1 hardware intervals.  The array 
       is not subject to garbage collection.
===========================================================================*/
#include <stdio.h>
#include "saclib.h"

interval *GETHIPARRAY(n)
	BDigit n;
{
	interval *A;

Step1: /* Allocate memory for array. */
	A = (interval *)malloc((n + 1)*sizeof(interval));
	if (A == NULL)
	   FAIL("GETHIPARRAY","Out of memory.");

Return: /* Prepare for return. */
	return(A);
}
