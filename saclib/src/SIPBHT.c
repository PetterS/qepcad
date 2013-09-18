/*==========================================================================
                              SIPBHT(A,k)

Soft-float interval polynomial binary homothetic transformation.

Inputs
   A : a software interval polynomial.
   k : a BETA-digit.
  
Effect
   A(x) is replaced by B(x) = A(2^k * x).
==========================================================================*/
#include "saclib.h"

void SIPBHT(A,k)
       BDigit *A,k;
{
       BDigit c,e,i,j,n,p;

Step1: /* Degree, precision. */
       n = A[0];
       p = A[3];

Step2: /* Compute new exponents. */
       c = p + 3;
       e = 0;
       i = 1;
       for (j = 0; j <= n; j++) {
	  A[i] = A[i] + e;
	  i = i + c;
	  A[i] = A[i] + e;
	  i = i + c;
	  e = e + k; }
	 
Return: /* Return. */
       return;
}
