/*===========================================================================
				ADDTO(A,B,n)

Add array to array.

Inputs
  A, B : arrays of length >= n containing non-negative BETA-digits.
  n    : positive BETA-digit.

Effect : B[0],...,B[n-1] is added to A[0],...,A[n-1],... (result in A).
===========================================================================*/
#include "saclib.h"

void ADDTO(A,B,n)
	Word *A,*B,n;
{
        Word c,cp,i;

Step1: /* Add. */
       cp = 0;
       for (i = 0; i < n; i++)
         {
         c = A[i] + B[i] + cp;
         if (c >= BETA)
           {
           c = c - BETA;
           cp = 1;
           }
         else
           cp = 0;
         A[i] = c;
         }

Step2: /* Propagate carry. */
       while (cp != 0)
         {
         c = A[i] + cp;
         if (c >= BETA)
           {
           c = c - BETA;
           cp = 1;
           }
         else
           cp =0;
         A[i] = c;
         i++;
         }

Return: /* Prepare for return. */
        return;
}
