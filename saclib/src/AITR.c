/*=======================================================================
                            AITR(A,n,k,B)

Array integer truncate and round.

Inputs
   A    : a nonzero integer in array representation.
   n, k : nonnegative BETA digits, with k < ZETA.
   B    : an array whose size is at least min(3,m - n + 3),
          where m = L(A).

Effect
   Let N = n * ZETA + k.  {A / 2^N}, the nearest integer to
       A / 2^N, is placed in the array B.
========================================================================*/
#include "saclib.h"

void AITR(A,n,k,B)
	BDigit *A,n,k,*B;
{
	BDigit a,a1,a2,i,m,kp;

Step1: /* B = 0. */
	m = A[1];
	if (m < n) {
	   B[0] = 0;
	   B[1] = 0;
	   B[3] = 0;
	   goto Return;}
	
Step2: /* Shift right. */
	kp = ZETA - k;
	for (i = n + 2; i <= m; i++) {
	   a1 = A[i] >> k;
	   a2 = (A[i + 1] << kp) & BETA1;
	   B[i - n] = a1 | a2; }
	B[m - n + 1] = A[m + 1] >> k;
	B[m - n + 2] = 0;

Step3: /* Round. */
	if (k > 0)
	   a = A[n +2] >> (k - 1);
	else {
	   if (n > 0)
	      a = A[n + 1] >> (ZETA - 1);
	   else
	      a = 0; }
	a = a & 1;
	i = 2;
	while (a > 0) {
	   a = B[i] + a;
	   B[i] = a & BETA1;
	   a = a >> ZETA;
	   i = i + 1; }

Step4: /* Store sign and length. */
	B[0] = A[0];
	if (B[m - n + 2] != 0)
	   B[1] = m - n + 1;
	else if (m > n && B[m - n + 1] != 0)
	   B[1] = m - n;
	else if (m - n >= 2 && B[m - n] != 0)
	   B[1] = m - n - 1;
	else {
	   B[1] = 0;
	   B[0] = 0; }

Return: /* Return. */
	return;
}
