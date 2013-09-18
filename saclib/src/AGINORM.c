/*=======================================================================
                        AGINORM(A,B,T1,T2)

Array Gaussian integer norm.

Inputs
   A : a Gaussian integer in array representation.
   B,T1,T2 : arrays for integers.  Their sizes must be at least
             2 n + 3, where n is the length of A.

Effect
   The norm of A is placed in B.
========================================================================*/
#include "saclib.h"

void AGINORM(A,B,T1,T2)
	BDigit **A,*B,*T1,*T2;
{

Step1: /* A = 0. */
	if (AGIZERO(A)) {
	   B[0] = 0;
	   B[1] = 0;
	   B[2] = 0;
	   goto Return; }

Step2: /* Real or imaginary part of A is zero. */
	if (AIZERO(A[0])) {
	   AIPROD(A[1],A[1],B);
	   goto Return; }
	if (AIZERO(A[1])) {
           AIPROD(A[0],A[0],B);           
           goto Return; }

Step3: /* Otherwise. */
	AIPROD(A[0],A[0],T1);
	AIPROD(A[1],A[1],T2);
	AISUM(T1,T2,B);

Return: /* Return. */
	return;
}
