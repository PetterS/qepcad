/*======================================================================
                        FPROD2(A,B,d,C)

Floating-point product, precision 2.

Inputs
   A, B : double-precision floating-point numbers.
   d : a sign (rounding direction).
   C : an array of size at least 5.

Output
   C : a double-precision floating-point number approximating the
       product of A and B.  If d = -1, C is the gretest double-
       precision floating-point number less than or equal to the
       product.  If d = +1, C is the least double -precision floating-
       point number greater than or equal to the product.  If d = 0, C is
       the nearest double-precision floating-point number to the product
       (if two are equally near, the one with even mantissa is chosen).
======================================================================*/
#include "saclib.h"

void FPROD2(A,B,d,C)
        Word *A,*B;
        BDigit d;
	Word *C;
{
        BDigit c2,c21,c22,c23,c3,c31,c32,c33,c34,c41,c42,s;

Step1: /* A or B zero. */
        if (A[1] == 0 || B[1] == 0) {
	   C[0] = 0;
           C[1] = 0;
	   C[2] = 0;
	goto Return; }

Step2: /* Compute exponent and sign. */
        C[0] = A[0] + B[0];
        if (A[1] == B[1])
           s = 1;
        else
           s = -1;

Step3: /* Compute mantissa. */
	DPRNN(A[3],B[3],&c21,&C[1]);
        DPRNN(A[4],B[3],&c31,&c22);
        DPRNN(A[3],B[4],&c32,&c23);
        DPRNN(A[4],B[4],&c41,&c33);
        c2 = c21 + c22 + c23;
        C[2] = c2 & BETA1;
        c34 = c2 >> ZETA;
        c3 = c31 + c32 + c33 + c34;
        C[3] = c3 & BETA1;
        c42 = c3 >> ZETA;
        C[4] = c41 + c42;

Step4: /* Normalize. */
	if (C[4] < BETA2) {
	   LSHIFT1(C+1,4);
	   C[0] = C[0] - 1; }

Step5: /* Rounding decision. */
	if (d != 0) {
	   if (d == s) {
	      if (C[2] != 0 || C[1] != 0)
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
	      if (C[1] != 0)
	         goto Step6;
	      else if (ODD(C[3]))
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

Step7: /* Store sign and precision. */
	C[1] = s;
	C[2] = 2;

Return: /* Return. */
	return;
}
