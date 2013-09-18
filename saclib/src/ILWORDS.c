/*===========================================================================
		       ILWORDS(A,m,B,n; a1,a0,b1,b0)

Integer leading words.

Inputs
  A, B: in Z, in array representation, A, B > 0.  If u and v are the
        bit-lengths of A and B, respectively, then u >= 2 * ZETA and
        u - v < ZETA.
  m, n: BETA digits, the word lengths of A and B, respectively.

Outputs
  a1, a0, b1, b0: BETA digits.
                  a1 consists of the leading ZETA bits of A.
                  a0 consists of the next ZETA bits of A after a1.
                  b1 consists of the leading (ZETA - u + v) bits of B.
                  b0 consists of the next ZETA bits of B after b1.
===========================================================================*/
#include "saclib.h"

void ILWORDS(A,m,B,n, a1_,a0_,b1_,b0_)
       Word *A,m,*B,n, *a1_,*a0_,*b1_,*b0_;
{
       Word a0,a1,b0,b1,d,e;

Step1: /* Get the leading words of A. */
       a1 = A[m-1];
       a0 = A[m-2];
       d = PDLOG2(a1);
       e = ZETA - d;
       if (e > 0) {
	  a1 = (a1 <<= e) | (a0 >> d);
	  a0 = (A[m-3] >> d) | ((a0 << e) & BETA1); }

Step2: /* Get the leading words of B. */
       b1 = B[n-1];
       b0 = B[n-2];
       if (m == n) {
	 if (n > 2) {  
	   b1 = (b1 << e) | (b0 >> d);
	   b0 = (B[n-3] >> d) | ((b0 << e) & BETA1); } }
       else {
	 b0 = (b0 >> d) | ((b1 << e) & BETA1);
	 b1 >>= d; }
	  
Return:	/* Prepare for return. */
       *a1_ = a1;
       *a0_ = a0;
       *b1_ = b1;
       *b0_ = b0;
       return;
}
