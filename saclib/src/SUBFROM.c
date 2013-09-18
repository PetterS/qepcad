/*===========================================================================
			       SUBFROM(A,B,n)

Subtract array from array.

Inputs
  A    : non-negative integer of length >= n in array representation
  B    : non-negative integer of length n in array representation.
         A - B >= 0.
  n    : positive BETA-digit.

Effect : B[0],...,B[n-1] is subtracted from A[0],...,A[n-1],...
         and the result is put in A.
===========================================================================*/
#include "saclib.h"

void SUBFROM(A,B,n)
	Word *A,*B,n;
{
        Word c,cp,i;

Step1: /* Subtract. */
       cp = 0;
       for (i = 0; i < n; i++)
         {
         c = A[i] - B[i] + cp;
         if (c < 0)
           {
           c = c + BETA;
           cp = -1;
           }
         else
           cp = 0;
         A[i] = c;
         }

Step2: /* Propagate borrow. */
       while (cp != 0)
         {
         c = A[i] + cp;
         if (c < 0)
           {
           c = c + BETA;
           cp = -1;
           }
         else
           cp =0;
         A[i] = c;
         i++;
         }

Return: /* Prepare for return. */
        return;
}
