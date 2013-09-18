/*===========================================================================
			    PRODUCT(A,n1,B,n2,C)

Integer product - array representation. Classical method.

Inputs
  n1,n2: positive BETA-digits.
  A, B : non-negative integers of lengths n1 and n2 in array representation.
  C    : an array of length >= n1 + n2 containing non-negative
         BETA-digits.

Effect : A * B is added to C.
===========================================================================*/
#include "saclib.h"

void PRODUCT(A,n1,B,n2,C)
        Word *A,n1,*B,n2,*C;
{
        Word b,c,c0,c1,cp,i,j,k;

Step1: /* Add rows of digit products. */
       for (j = 0; j < n2; j++)
         {
         b = B[j];
         k = j;
         cp = 0;
         for (i = 0; i < n1; i++)
           {
           DPR(A[i],b,&c1,&c0);
           c = C[k] + c0 + cp;
           cp = c >> ZETA;
           C[k] = c & BETA1;
           cp = cp + c1;
           k++;
           }
         while (cp != 0)
           {
           c = C[k] + cp;
           if (c >= BETA)
             {
             c = c - BETA;
             cp = 1;
             }
           else
             cp =0;
           C[k] = c;
           k++;
	   }
         }

Return: /* Prepare for return. */
        return;
}
