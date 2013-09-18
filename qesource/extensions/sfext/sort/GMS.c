/*======================================================================
                      GIS(A,m,C)

General merge sort.

Inputs
A : An array of m words.
m : A positive BETA-digit.
C : A pointer to a function of two arguments returning type Word.
Side Effects
    Rearranges the values in A so that they are in sorted order.
  ======================================================================*/
#include "mysort.h"


void GMS(Word *A, Word m,Word (*C)(Word,Word))
{
       Word *T,*A1,*A2,m1,m2,k;

Step0: /* No sorting to do */
       if (m < 2) goto Return;

Step1: /* Split. */
       m1 = m >> 1;
       m2 = m1 + ODD(m);
       A1 = A;
       A2 = A + m1;

Step2: /* Sort sublists. */
       if (m1 <= 3) {
	 GIS(A1,m1,C);
	 GIS(A2,m2,C); }
       else {
	 GMS(A1,m1,C);
	 GMS(A2,m2,C); }

Step3: /* Copy A1 into a temporary array. */
       T = GETARRAY(m1);
       for(k = 0; k < m1; k++) T[k] = A1[k];
       A1 = T;

Step4: /* Merge A1 and A2 until one or both is exhausted. */
       for(k = 0; (m1 > 0) && (m2 > 0); k++) {
	 if (C(A1[0],A2[0]) > 0) {
	   A[k] = A2[0]; A2++; m2--; }
	 else {
	   A[k] = A1[0]; A1++; m1--; } }

Step5: /* Complete merge. */
       while (m1 > 0) {
	 A[k++] = A1[0]; A1++; m1--; }
       FREEARRAY(T);

Return: /* Prepare to return. */
       return;
}
