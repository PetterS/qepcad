/*===========================================================================
			   ILWORD(A,m,B,n; a,b)

Integer leading word.

Inputs
  A, B: in Z, in array representation, A, B > 0.  If u and v are the
        bit-lengths of A and B, respectively, then u >= ZETA and
        0 <= u - v < ZETA.
  m, n: BETA digits, the word lengths of A and B, respectively.

Output
  a : a BETA digit, the leading ZETA bits of A.
  b : a BETA digit, the leading (ZETA - u + v) bits of B.
===========================================================================*/
#include "saclib.h"

void ILWORD(A,m,B,n, a_,b_)
       Word *A,m,*B,n, *a_,*b_;
{
       Word a,b,d,e;

Step1: /* Get leading word of A. */
       a = A[m-1];
       d = PDLOG2(a);
       e = ZETA - d;
       if (e > 0)
	  a = (a << e) | (A[m-2] >> d);

Step2: /* Get leading word of B. */
       b = B[n-1];
       if (m == n) {
	 if (n > 1)
	   b = (b << e) | (B[n-2] >> d); }
       else
	 b = b >> d;
       
Return: /* Prepare for return. */
       *a_ = a;
       *b_ = b;
       return;
}
