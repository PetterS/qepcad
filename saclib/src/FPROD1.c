/*======================================================================
                        FPROD1(A,B,d,C)

Floating-point product, precision 1.

Inputs
   A, B : single-precision floating-point numbers.
   d : a sign (rounding direction).
   C : an array of size at least 4.

Output
   C : a single-precision floating-point number approximating the
       product of A and B.
       If d = -1, C is the greatest single-precision floating-point
       number less than or equal to the product.
       If d = +1, C is the least single-precision floating-point
       number greater than or equal to the product.
       If d = 0, C is the nearest single-precision floating-point
       number to the product (if two are equally near, the one with
       even mantissa is chosen).
======================================================================*/
#include "saclib.h"

void FPROD1(A,B,d,C)
        Word *A,*B;
        BDigit d;
	Word *C;
{
	BDigit f,g,t;

Step1: /* A or B zero. */
        if (A[1] == 0 || B[1] == 0) {
	  C[1] = 0;
	  C[2] = 1;
	  goto Return; }

Step2: /* Compute exponent, sign and precision. */
	C[0] = A[0] + B[0];
	if (A[1] == B[1])
	  C[1] = 1;
        else
	  C[1] = -1;
	C[2] = 1;

Step3: /* Multiply. */
	DPRNN(A[3],B[3], &f,&g);

Step4: /* Normalize. */
        if (f < BETA2) {
	  t = g;
	  g = g << 1 & BETA1;
	  t = t >> (ZETA - 1);
	  f = f << 1 | t;
	  C[0] = C[0] - 1; }

Step5: /* Round. */
        if (d != 0) {
	  if (d == C[1] && g != 0)
	    f = f + 1; }
        else if (g >= BETA2) {
	  if (g > BETA2) {
	    f = f + 1; }
	  else if (ODD(f)) {
	    f = f + 1; } }
	if (f == BETA) {
	  C[3] = BETA2;
	  C[0] = C[0] + 1; }
	else
	  C[3] = f;

Return: /* Return. */
	return;
}
