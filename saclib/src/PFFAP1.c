/*=======================================================================
                         C <- PFFAP1(p,A,B)

Medium prime finite field array for plus 1.

Inputs
   p : a prime beta digit.
   A : an array of p beta digits such that A[0] = 0 and, for 0 < i < q,
       A[i] = g^i, where g is a generator of the field.
   B : an array of p beta digits such that B[i] = j if and only if
       A[j] = i.

Output
   C : an array of p beta-integers.  For 0 <= i < p, i is the
       discrete logarithm of some a in Z_p and C[i] is the
       discrete logarithm of a +1 in Z_p.
=======================================================================*/
#include "saclib.h"

BDigit *PFFAP1(p,A,B)
	BDigit p,*A,*B;
{
	BDigit a,b,i;
	BDigit *C;

Step1: /* Use arrays A and B. */
	C = GETARRAY(p);
	C[0] = p - 1;
	for (i = 1; i < p; i++) {
	   a = A[i];
	   if (a == p - 1)
	      b = 0;
	   else
	      b = a + 1;
	   C[i] = B[b]; }

Return: /* Return C. */
	return (C);
}
