/*=======================================================================
                            a <- AITRS(A,n,k)

Array integer truncate and round, small result.

Inputs
   A : an integer in array representation.
   n, k : nonnegative BETA digits, with 0 <= k < ZETA.  Let m =
	  n * ZETA + k.  The bit length of A is less than
	  m + ZETA.

Output
   a : a BETA digit.  a = sign(A) * {(|A| / 2^m)}, where {x}
       denotes the nearest integer to x.
========================================================================*/
#include "saclib.h"

BDigit AITRS(A,n,k)
	BDigit *A,n,k;
{
	BDigit a,b,c,d,h,p;;

Step1: /* A = 0. */
	if (A[0] == 0) {
	   a = 0;
	   goto Return; }

Step2: /* Divide by 2^m. */
	p = A[1];
	b = A[p + 1];
	h = PDLOG2(b);
	if (p - 1 == n)
	   a = b >> k;
	else if (p - 1 > n) {
	   c = A[p];
	   a = ((b << (ZETA - k)) | (c >> k)); }
	else
	   a = 0;

Steo3: /* Round. */
	if (p - 1 == n) {
	   if (h <= k)
	      d = 0;
	   else
	      d = (b >> (k - 1)) & 1; }
	else if (p - 1 > n) {
	   if (k == 0)
	      d = (A[p - 1] >> (ZETA -1)) & 1;
	   else
	      d = (A[p] >> (k - 1)) & 1; }
	else
	   d = 0;
	a = a + d;

Step4: /* Confer the sign of A. */
	if (A[0] < 0)
	   a = - a;

Return: /* Return a. */
	return(a);
}
