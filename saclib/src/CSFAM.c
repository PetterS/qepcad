/*=======================================================================
                         c = CSFAM(n,A)

Characteristic set from array of members.

Inputs
   n ; a beta digit, 1 <= n <= zeta.
   A : an array of n beta digits.  0 <= A[0] < A[1] < ... < A[n-1]
       < zeta.

Output
   c : a beta digit.  A represents a subset of {0,1,...,zeta - 1}.
       c is the characteristic set of A.  Bit i of c is 1 if and
       only if A[j] = i for some j.
=======================================================================*/
#include "saclib.h"

BDigit CSFAM(n,A)
	BDigit n,*A;
{
	BDigit c,i;

Step1: /* Shift and add. */
	c = 0;
	for (i = 0; i < n; i++)
	   c = c | (1 << A[i]);

Return: /* Return c. */
	return(c);
}
