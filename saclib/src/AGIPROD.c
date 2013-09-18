/*=======================================================================
                        AGIPROD(A,B,C,T1,T2)

Array Gaussian integer product.

Inputs
   A,B : Gaussian integers in array representation.
   C   : an array for a Gaussian integer.  Let m = L(A), n = L(B).
         The sizes of C[0] and C[1] must be at least m + n + 3.
   T1,T2 : arrays for integers.  Their sizes must be at least
           m + n + 3.

Effect
   The product of A and B is placed in C.
========================================================================*/
#include "saclib.h"

void AGIPROD(A,B,C,T1,T2)
	BDigit **A,**B,**C,*T1,*T2;
{

Step1: /* Compute the real part of C. */
	AIPROD(A[0],B[0],T1);
	AIPROD(A[1],B[1],T2);
	T2[0] = - T2[0];
	AISUM(T1,T2,C[0]);

Step2: /* Compute the imaginary part of C. */
	AIPROD(A[0],B[1],T1);
	AIPROD(A[1],B[0],T2);
	AISUM(T1,T2,C[1]);

Return: /* Return. */
	return;
}
