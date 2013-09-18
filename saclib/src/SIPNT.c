/*======================================================================
		   	SIPNT(A,B)

Software interval polynomial negative transformation.

Inputs
   A : a software interval polynomial.
   B : an array large enough for an interval polynomial having
       the same degree and precision as A.

Effect
   The interval polynomial A(-x) is placed in B.
======================================================================*/
#include "saclib.h"

void SIPNT(A,B)
	BDigit *A,*B;
{
	BDigit i,j,n,p,q1,q2,S;

Step1: /* Compute sizes. */
	n = A[0];
	p = A[3];
	q1 = p + 3;
	q2 = q1 + q1;

Step2: /* Copy degree. */
	B[0] = A[0];

Step3: /* Copy coefficients, some negated. */
	S = 1;
	for (i = 0; i <= n; i++) {
	   if (EVEN(i)) {
	      for (j = 0; j < q2; j++)
	         B[S+j] = A[S+j]; }
	   else {
	      for (j = 0; j < q1; j++) 
	         B[S+j] = A[S+q1+j];
	      for (j = 0; j < q1; j++)
	         B[S+q1+j] = A[S+j];
	      B[S+1] = - B[S+1];
	      B[S+q1+1] = - B[S+q1+1]; }
	   S = S + q2; }
	   
Return: /* Return. */
	return;
}
