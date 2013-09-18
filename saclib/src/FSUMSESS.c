/*======================================================================
                        FSUMSESS(A,B,d,C)

Floating-point sum, same exponents, same signs.

Inputs
   A, B : two floating-point numbers having the same precisions, the
          same exponents and the same signs.
   d :    a sign (rounding direction).
   C :    an array large enough for the sum.

Output
   C :    a floating-point number approximating the sum of A and B,
          rounded according to IEEE standards.
======================================================================*/
#include "saclib.h"

void FSUMSESS(A,B,d,C)
	Word *A,*B;
        BDigit d;
	Word *C;
{
        BDigit c,e,f,i,p,r,s;

Step1: /* Store exponent, sign and precision. */
        C[0] = A[0] + 1;
        s = A[1];
        C[1] = s;
        p = A[2];
        C[2] = p;

Step2: /* Set the rounding flag. */
	e = A[3] + B[3];
	if ((d == s && (e & 1)) || (d == 0 && (e & 1) && (e & 2)))
	  r = 1;
	else
	  r = 0;

Step3: /* Add and shift right one bit. */
        for (i = 4; i <= p+2; i++) {
	  c = e >> ZETA;
	  f = e & BETA1;
	  e = A[i] + B[i] + c;
	  C[i-1] = (f>>1) | ((e & 1) << (ZETA-1)); }
	C[p+2] = e >> 1;

Step4: /* Round up if needed. */
        if (r == 1) {
           C[3] = C[3] + 1;
           i = 3;
           while (C[i] == BETA) {
              C[i] = 0;
              i = i + 1;
              C[i] = C[i] + 1; } }

Return: /* Return. */
        return;
}
