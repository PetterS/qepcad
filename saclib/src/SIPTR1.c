/*======================================================================
                           SIPTR1(A,B)

Software interval polynomial translation by 1.

Inputs
   A : a software interval polynomial of positive degree.
   B : an array large enough for A(x + 1).

Effect
    The software interval polynomial  A(x + 1) is placed in B.
======================================================================*/
#include "saclib.h"

void SIPTR1(A,B)
	BDigit *A,*B;
{
	BDigit i,j,n,p,q1,q2,t;
	BDigit *Ap,*Bp,*C,*Cp,*Dp;

Step1: /* Get sizes. */
	n = A[0];
	p = A[3];
	q1 = p + 3;
	q2 = q1 + q1;
	t = n * q2;

Step2: /* Get an array C. */
	C = GETARRAY(t + q2 + 1);

Step3: /* Start with array B if n is even, else with array C. */
	Ap = A + 1;
	if (EVEN(n)) {
	   Bp = B + 1;
	   Cp = C + 1; }
	else {
	   Bp = C + 1;
	   Cp = B + 1; }

Step4: /* Apply Horner's method. */
	SICOPY(Ap + t,Bp + t);
	SICOPY(Ap + t,Cp + t);
	for (j = t; j > 0; j = j - q2) {
	   SISUM(Ap + j - q2,Bp + j,Cp + j - q2);
	   for (i = j; i < t; i = i + q2)
	      SISUM(Bp + i,Bp + i + q2,Cp + i);
	   Dp = Bp;
	   Bp = Cp;
	   Cp = Dp; }

Step5: /* Store the degree in B. */
	B[0] = n;

Step6: /* Free array C. */
	FREEARRAY(C);

Return: /* Return. */
	return;
}
