/*======================================================================
                          SIPR(A,B)

Software-float interval polynomial reciprocal transformation.

Inputs
  A : a polynomial in SI[X].
  B : an array large enough for a copy of A.

Effect
  B contains the software-float interval polynomial B(x) = x^n A(1/x).
======================================================================*/
#include "saclib.h"

void SIPR(A,B)
       Word *A, *B;
{
       BDigit c,i,j,k,n,p;

Step1: /* Degree, precision, interval length. */
       n = A[0];
       p = A[3];
       c = 2 * p + 6;

Step2: /* Degree. */
       B[0] = n;

Step3: /* b_k <- a_(n-k) for k = 0,...,n. */
       i = c * n + 1;
       j = 1;
       for (k=0;k<=n;k++) {
	 SICOPY(A + i,B + j);
	 i = i - c;
	 j = j + c; }
}
