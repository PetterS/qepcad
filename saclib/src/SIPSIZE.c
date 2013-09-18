/*======================================================================
                      S <- SIPSIZE(A)

Software interval polynomial size.

Input
   A : a software interval polynomial.

Output
   S : the size of an array needed for a polynomial having the
       same degree and same precision as A.
======================================================================*/
#include "saclib.h"

BDigit SIPSIZE(A)
	BDigit *A;
{
	BDigit n,p,q1,q2,S;

Step1: /* Compute the size. */
	n = A[0];
	p = A[3];
	q1 = p + 3;
	q2 = q1 + q1;
	S = (n + 1) * q2 + 1;

Return: /* Return S. */
	return(S);
}
