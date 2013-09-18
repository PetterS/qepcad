/*=======================================================================
                        AIMP2(A,h,B)

Array integer multiplication by a power of 2.

Inputs
   A : an array integer.
   h : a nonnegative BETA integer.
   B : an array.  Let m = [h / ZETA], n = L(A).  The size of B must 
       be at least m + n + 3.

Effect
   2^h * A is placed in the array B.
========================================================================*/
#include "saclib.h"

void AIMP2(A,h,B)
        BDigit *A,h,*B;
{
	BDigit b,i,k,kp,m,n,p;

Step1: /* A = 0 or h = 0. */
	if (A[0] == 0 || h == 0) {
	   AICOPY(A,B);
           goto Return; }

Step2: /* Express h as m * ZETA + k. */
	if (h < ZETA) {
	   m = 0;
	   k = h; }
	else {
	   m = h / ZETA;
	   k = h - m * ZETA; }
	
Step3: /* Get n annd set p = m + n. */
	n = A[1];
	p = n + m;

Step4: /* Shift. */
	kp = ZETA - k;
	B[p + 2] = A[n + 1] >> kp;
	for (i = n + 1; i > 2; i--) {
	   b = (A[i] << k) & BETA1;
	   B[i +m] = (A[i - 1] >> kp) | b; }
	B[m + 2] = (A[2] << k) & BETA1;
	for (i = 2; i < m + 2; i++)
	   B[i] = 0;

Step5: /* Insert length and sign. */
	if (B[p + 2] != 0)
	   B[1] = p + 1;
	else
	   B[1] = p;
	B[0] = A[0];
	   
Return: /* Return. */
	return;
}
