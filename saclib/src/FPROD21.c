/*======================================================================
                        FPROD21(A,B,d,C)

Floating-point product, precision 2 by precision 1.

Inputs
   A : a double-precision floating-point number.
   B : a single-precision number.
   d : a sign (rounding direction).
   C : an array of size at least 5.

Output
   C : a double-precision floating-point number approximating the
       product of A and B.
       If d = -1, C is the greatest double-precision floating-point
       number less than or equal to the product.
       If d = +1, C is the least double-precision floating-point
       number greater than or equal to the product.
       If d = 0, C is the nearest double-precision floating-point
       number to the product (if two are equally near, the one with
       even mantissa is chosen).
======================================================================*/
#include "saclib.h"

void FPROD21(A,B,d,C)
        Word *A,*B;
        BDigit d;
	Word *C;
{
        BDigit c3,c31,c32,c41,c42;

Step1: /* A or B zero. */
        if (A[1] == 0 || B[1] == 0) {
           C[1] = 0;
           C[2] = 2;
        goto Return; }

Step2: /* Compute exponent and sign. */
        C[0] = A[0] + B[0]; 
        if (A[1] == B[1])
           C[1] = 1;
        else
           C[1] = -1;

Step3: /* Compute mantissa. */
	DPRNN(A[3],B[3],&c31,&C[2]);
	DPRNN(A[4],B[3],&c41,&c32);
	c3 = c31 + c32;
	C[3] = c3 & BETA1;
	c42 = c3 >> ZETA;
	C[4] = c41 + c42;

Step4: /* Normalize. */
	if (C[4] < BETA2) {
           LSHIFT1(C+2,3);   
           C[0] = C[0] - 1; }

Step5: /* Rounding decision. */
        if (d != 0) {
           if (d == C[1]) {
              if (C[2] != 0)
                 goto Step6;
              else
                 goto Step7; }
           else
              goto Step7; }
        else {
           if (C[2] > BETA2)
              goto Step6;
           else if (C[2] < BETA2)
              goto Step7;
           else {
              if (ODD(C[3]))
                 goto Step6;
              else
                 goto Step7; } }

Step6: /* Round up. */
        C[3] = C[3] + 1;
        if (C[3] == BETA) {
           C[3] = 0;
           C[4] = C[4] + 1;
           if (C[4] == BETA) {
              C[4] = BETA2;
              C[0] = C[0] + 1; } }

Step7: /* Store precision. */
        C[2] = 2;

Return: /* Return. */
        return;
}
