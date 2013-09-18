/*===========================================================================
			    IPRODA(A,n1,B,n2,C)

Integer product - array representation. Classical algorithm.

Inputs
  n1,n2: positive beta-digits.
  A, B : non-negative integers of lengths n1 and n2 in array representation.
  C    : an array of length n1 + n2.

Effect : C = A * B in array representation.
===========================================================================*/
#include "saclib.h"

void IPRODA(A,n1,B,n2,C)
        Word *A,n1,*B,n2,*C;
{
        Word b,c,c0,c1,cp,i,j,k;

Step1: /* Initialize with first row of digit products. */
       b = B[0];
       cp = 0;
       for (i = 0; i < n1; i++) {
	  DPR(A[i],b,&c1,&c0);
	  c = c0 + cp;
	  cp = c >> ZETA;
	  C[i] = c & BETA1;
	  cp = cp + c1; }
       C[n1] = cp;

Step2: /* Add rows of digit products. */
       for (j = 1; j < n2; j++) {
	  b = B[j];
	  k = j;
	  cp = 0;
	  for (i = 0; i < n1; i++) {
	     DPR(A[i],b,&c1,&c0);
	     c = C[k] + c0 + cp;
	     cp = c >> ZETA;
	     C[k] = c & BETA1;
	     cp = cp + c1;
	     k++; }
	  C[k] = cp; }

Return: /* Prepare for return. */
	return;
}
