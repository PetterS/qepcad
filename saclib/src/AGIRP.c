/*======================================================================
                        AGIRP(A,B,T; k)

Array Gaussian integer reduced part.

Inputs
   A : a nonzero array Gaussian integer.
   B : an array for the result.
   T : an auxilliary Gaussian integer array.

Output
   k : a nonnegative BETA digit.  (1 + i)^k divides A, but
       (1 + i)^{k + 1} does not.

Effect
   An associate of A / (1 + i)^k is placed in B.
======================================================================*/
#include "saclib.h"

void AGIRP(A,B,T, k_)
	BDigit **A,**B,**T, *k_;
{
	BDigit *A1,*A2,a1,a2,h,i,k,n,n1,n2;

Step1: /* Compute h = floor(k/2). */
	A1 = A[0];
	A2 = A[1];
	n1 = A1[1];
	n2 = A2[1];
	n = MIN(n1,n2);
	h = 0;
	i = 0;
	while (i <= n) {
	   a1 = A1[i + 2];
	   a2 = A2[i + 2];
	   if (a1 == 0 && a2 == 0) {
	      h = h + ZETA;
	      i = i + 1; }
	   else {
	      while (!(a1 & 1) && !(a2 & 1)) {
	         h = h + 1;
	         a1 = a1 >> 1;
	         a2 = a2 >> 1; }
	      goto Step2; } }

Step2: /* If A is divisible by 1 + 1, multiply A  by 1 - i,
          add 1 to k, and divide by 2^{h + 1}.  Otherwise
          divide A by 2^h. */
	k = h + h;
	if ((a1 & 1 == 1) && (a2 & 1 == 1)) {
	   A1[0] = - A1[0];
	   AISUM(A1,A2,B[1]);
	   A1[0] = - A1[0];
	   AISUM(A1,A2,B[0]);
	   k = k + 1;
	   AGIDP2(B,h + 1,B); }
	else 
	   AGIDP2(A,h,B);

Return: /* Return k. */
	*k_ = k;
	return;
}
