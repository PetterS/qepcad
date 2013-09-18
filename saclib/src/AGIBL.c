/*=======================================================================
                            AGIBL(A; n,k)

Array Gaussian integer bit length.

Input
   A : a Gaussian integer in array representation.

Outputs
   n, k : nonnegative BETA digits.  The bit length of A, that is, 
          the maximum of the bit lengths of the real and imaginary
          parts of A, is equal to n * ZETA + k, 0 <= k < ZETA.  (The
          bit length of the integer 0 is defined to be 0.)
========================================================================*/
#include "saclib.h"

void AGIBL(A, n_,k_)
	BDigit **A,*n_,*k_;
{
	BDigit *A1,*A2,a,k,n,n1,n2;

Step1: /*  Determine which part is longer, then how long it is. */
	A1 = A[0];
	A2 = A[1];
	n1 = A1[1];
	n2 = A2[1];
	if (n1 > n2) {
	   n = n1 - 1;
	   a = A1[n1 + 1]; }
	else if (n2 > n1) {
	   n = n2 - 1;
	   a = A2[n2 + 1]; }
	else {
	   if (n1 == 0) {
	      n = 0;
 	      k = 0;
	      goto Return; }
	   n = n1 - 1;
	   if (A1[n1 + 1] > A2[n2 + 1])
	      a = A1[n1 + 1];
	   else
	      a = A2[n2 + 1]; }
	k = DLOG2(a);
	if (k == ZETA) {
	   n = n + 1;
	   k = 0; }

Return: /* Return n and k. */
	*n_ = n;
	*k_ = k;
	return;
}
