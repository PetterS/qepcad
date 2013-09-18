/*======================================================================
                      L <- PERMR(n)

Permutation, random.

Inputs
  n : a BETA-digit, 0 < n <= 100.

Outputs
  L : a list of the first n positive integers in random order.
======================================================================*/
#include "saclib.h"

Word PERMR(n)
       Word n;
{
       Word A[101],L,i,j,t;
       /* hide i,j,t; */

Step1: /* Initialize array. */
       for (i = 1; i <= n; i++)
         A[i] = i;

Step2: /* Random interchanges. */
       for (j = n; j >= 1; j--)
         {
         i = MDRAN(j) + 1;
         t = A[i];
         A[i] = A[j];
         A[j] = t;
         }

Step3: /* Form list. */
       L = NIL;
       for (i = 1; i <= n; i++)
         L = COMP(A[i],L);

Return: /* Prepare for return. */
       return(L);
}
