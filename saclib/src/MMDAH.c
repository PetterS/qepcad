/*===========================================================================
                          MMDAH(p,A,n)

Matrix of modular digits array representation - convert to Hessenberg form.

Input
  p : a BETA-digit, prime.
  A : an (n x n)-matrix over GF(p) in array representation,
  n : a positive BETA-digit.

Side effect
  A is transformed into a similar matrix of Hessenberg form (one that is
  zero everywhere below the first diagonal).
===========================================================================*/
#include "saclib.h"

void MMDAH(p,A,n)
       BDigit p;
       Word **A;
       BDigit n;
{
       BDigit a,ap,as,i,j,k,T;

Step1: /* Matrix order < 3. */
       if (n < 3)
	 goto Return;

Step2: /* First pivot step. */
       k = 1;

Step3: /* Find pivot row, if possible. */
       i = k;
       while (i < n && A[i][k-1] == 0)
	 i++;

Step4: /* No pivot row. */
       if (i == n)
	 goto Step7;

Step5: /* Row i is pivot row. */
       if (i > k) {
	 for (j = k-1; j < n; j++) { /* swap rows k and i. */
	   T = A[k][j];
	   A[k][j] = A[i][j];
	   A[i][j] = T; }
	 for (j = 0; j < n; j++) { /* swap columns k and i. */
	   T = A[j][k];
	   A[j][k] = A[j][i];
	   A[j][i] = T; } }

Step6: /* Row k is pivot row. */
       a = A[k][k-1];
       ap = MDINV(p,a);
       for (i = k+1; i < n; i++) {
	 as = MDPROD(p,A[i][k-1],ap);
	 for (j = k-1; j < n; j++)   /* transform row i by row k. */
	   A[i][j] = MDDIF(p,A[i][j],MDPROD(p,as,A[k][j]));
	 for (j = 0; j < n; j++)   /* transform column k by column i. */
	   A[j][k] = MDSUM(p,A[j][k],MDPROD(p,as,A[j][i])); }

Step7: /* Next pivot step. */
       k++;
       if (k < n-1)
	 goto Step3;

Return: /* Prepare for return. */
        return;
}
