/*=======================================================================
                         C <- MPFFAP1(p,q,A,B)

Medium prime finite field array for plus 1.

Inputs
   p : a medium prime beta digit.
   q : the size of a finite field GF(p^n), a beta digit.
   A : an array of q beta digits such that A[0] = 0 and for 0 < i < q,
       A[i] = G^i(p), where G is a generator of the field.  G^i is
       evaluated at p in Z, not in Z^p.
   B : an array of q beta-integers such that B[i] = j if and only if
       A[j] = i.

Output
   C : an array of q beta digits.  For 0 <= i < q, i is the
       discrete logarithm of some a in GF(p^n) and C[i] is the
       discrete logarithm of a + 1 in GF(p^n).
=======================================================================*/
#include "saclib.h"

BDigit *MPFFAP1(p,q,A,B)
	BDigit p,q,*A,*B;
{
	BDigit a,b,i,r;
	BDigit *C;

Step1: /* Use arrays A and B. */
	C = GETARRAY(q);
	C[0] = q - 1;
	for (i = 1; i < q; i++) {
	   a = A[i];
	   r = a % p;
	   if (r == p - 1)
	      b = a - r;
	   else
	      b = a + 1;
	   C[i] = B[b]; }

Return: /* Return C. */
	return (C);
}
