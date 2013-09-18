/*=======================================================================
			AIPROD(A,B,C)

Array integer product.

Inputs
   A, B : integers in array representation.
   C    : an array at least as long as the sum of the lengths
          of A and B plus 2.

Effect
   The product of A and B is placed in C.
========================================================================*/
#include "saclib.h"

void AIPROD(A,B,C)
	BDigit *A,*B,*C;
{
	BDigit b,c,c0,c1,cp,i,j,k,m,n;
	BDigit *Ap,*Bp,*Cp;

Step1: /* A or B zero. */
	if (A[0] == 0 || B[0] == 0) {
	   C[0] = 0;
	   C[1] = 0;
	   C[2] = 0;
	   goto Return; }

Step2: /* Let A' be the longer, B' the shorter. */
	if (A[1] >= B[1]) {
	   m = A[1];
	   n = B[1];
	   Ap = A + 2;
	   Bp = B + 2; }
	else {
	   m = B[1];
	   n = A[1];
	   Ap = B + 2;
	   Bp = A + 2; }

Step3: /* Multiply A' by the low order digit of B'. */
	Cp = C + 2;
	b = Bp[0];
	if (b == 1) {
	   for (i = 0; i < m; i++)
	      Cp[i] = Ap[i];
	   cp = 0;
	   goto Step4; }
	else if (b == 2) {
	   cp = 0;
	   for (i = 0; i < m; i++) {
	      c = (Ap[i] << 1) | cp;
	      cp = c >> ZETA;
	      Cp[i] =  c & BETA1; }
	   Cp[m] = cp;
	   goto Step4; }
	else if (b == 3) {
	   cp = 0;
	   for (i = 0; i < m; i++) {
	      c = (Ap[i] << 1) + Ap[i] + cp;
	      cp = c >> ZETA;
              Cp[i] =  c & BETA1; }
	   Cp[m] = cp;
           goto Step4; }
	else if (b == 4) {
           cp = 0;
           for (i = 0; i < m; i++) {
              c = (Ap[i] << 2) | cp;
              cp = c >> ZETA;
              Cp[i] =  c & BETA1; }
           Cp[m] = cp;
           goto Step4; }
	cp = 0;
        for (i = 0; i < m; i++) {
           DPR(Ap[i],b,&c1,&c0);
           c = c0 + cp;
           cp = c >> ZETA;
           Cp[i] = c & BETA1;
           cp = cp + c1; }
        Cp[m] = cp;

Step4: /* Complete the product. */
	for (j = 1; j < n; j++) {
           b = Bp[j];
           k = j;
           cp = 0;
           for (i = 0; i < m; i++) {
              DPR(Ap[i],b,&c1,&c0);
              c = Cp[k] + c0 + cp;
              cp = c >> ZETA;
              Cp[k] = c & BETA1;
              cp = cp + c1;
              k++; }
           Cp[k] = cp; }

Step5: /* Store the length and sign. */
	if (cp != 0)
	   C[1] = m + n;
	else
	   C[1] = m + n - 1;
	if (A[0] == B[0])
	   C[0] = 1;
	else
	   C[0] = -1;

Return: /* Return. */
	return;
}
