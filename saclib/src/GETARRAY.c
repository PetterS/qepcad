/*==========================================================================
                              A <- GETARRAY(n)

Get array.

Input
  n : a BETA-digit, n > 0.

Output
  A : a pointer to an array of n Words.  The array is not subject to
      garbage collection.
===========================================================================*/
#include <stdio.h>
#include "saclib.h"

Word *GETARRAY(n)
       Word n;
{
       Word *A;

Step1: /* Allocate memory for array. */
       A = (Word *)malloc((n)*sizeof(Word));
       if (A==NULL)
	  FAIL("GETARRAY","Out of memory.");

Return: /* Prepare for return. */
       return(A);
}
