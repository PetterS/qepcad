/*======================================================================
                      ISPROD(A,n1,B,n2,C)

Integer special short product.

Inputs
  n1,n2: BETA-digits, n1 >= n2 >= 2.
  A    : positive integer of length n1 in array representation.
  B    : positive integer of length n2 in array representation.
  C    : array of length >= n1 + 2.

Effect
  A X_n2 B is written into C.
  This means that if
  a_h, h = 1,...,n1, are the BETA-digits in A (low order to high order),
  b_j, j = 1,...,n2, are the BETA-digits in B, then
  C = sum_{h = 1,...,n1; j = 1,...,n2; h + j >= n2} a_h b_j BETA^(h+j-n2).
======================================================================*/
#include "saclib.h"

void ISPROD(A,n1,B,n2,C)
	Word *A;
        BDigit n1;
	Word *B;
	BDigit n2;
	Word *C;
{
        BDigit b,c0,c1,cp,i,j,k;
	Word c;

Step1: /* Initialize with first row of digit products. */
       b = B[0];
       k = 0;
       cp = 0;
       for (i = n2 - 2; i < n1; i++)
         {
         DPRNN(A[i],b,&c1,&c0);
         c = c0 + cp;
         cp = c >> ZETA;
         C[k] = c & BETA1;
         cp = cp + c1;
         k++;
         }
       C[k] = cp;

Step2: /* Add rows of digit products. */
       for (j = 1; j < n2 - 1; j++)
         {
         b = B[j];
         k = 0;
         cp = 0;
         for (i = n2 - j - 2; i < n1; i++)
           {
           DPRNN(A[i],b,&c1,&c0);
           c = C[k] + c0 + cp;
           cp = c >> ZETA;
           c  = c & BETA1;
           C[k] = c;
           cp = cp + c1;
           k++;
           }
         C[k] = cp;
         }

Step3: /* Add last row of digit products. */
       b = B[n2 - 1];
       k = 1;
       cp = 0;
       for (i = 0; i < n1; i++)
         {
         DPRNN(A[i],b,&c1,&c0);
         c = C[k] + c0 + cp;
         cp = c >> ZETA;
         c  = c & BETA1;
         C[k] = c;
         cp = cp + c1;
         k++;
         }
       C[k] = cp;

Return: /* Prepare for return. */
	return;
}
