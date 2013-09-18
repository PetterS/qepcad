/*=======================================================================
                        AIDP2(A,k,B)

Array integer division by a power of 2.

Inputs
   A : an array integer.
   k : a BETA integer, 0 <= k < ZETA.
   B : an array large enough for the result.

Effect
   The integral part of A / 2^k is placed in B.  Note that B may
   be the same array as A.
========================================================================*/
#include "saclib.h"

void AIDP2(A,k,B)
	BDigit *A,k,*B;
{
	BDigit *Ap,*Bp,i,kp,n;

Step1: /* Either A = 0 or k = 0. */
	if (A[0] == 0 || k == 0) {
	   if (A != B)
	      AICOPY(A,B);
	   goto Return; }

Step2: /* Shift. */
	n = A[1];
	Ap = A + 2;
	Bp = B + 2;
	kp = ZETA - k;
	for (i = 0; i <= n - 2; i++)
	   Bp[i] = (Ap[i] >> k) | ((Ap[i + 1] << kp) & BETA1);
	Bp[n - 1] = Ap[n - 1] >> k;
	B[0] = A[0];
	B[1] = A[1];
	if (Bp[n - 1] == 0)
	   B[1] = B[1] - 1;
	if (B[1] == 0 && Bp[0] == 0)
	   B[0] = 0;

Return: /* Return. */
	return;
}
