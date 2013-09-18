/*======================================================================
                      P <- PARTR(n)

Partition, random.

Inputs
  n : a BETA-digit, 0 < n <= 100.

Outputs
  P : a partition of n whose elements are the cycle lengths
      of a random n-permutation.
======================================================================*/
#include "saclib.h"

Word PARTR(n)
       Word n;
{
       Word A[101],P,h,i,j,k;
       /* hide h,i,j,k; */

Step1: /* Generate random permutation. */
       for (i = 1; i <= n; i++)
         A[i] = i;
       for (j = n; j >= 2; j--)
         {
         i = MDRAN(j) + 1;
         k = A[i];
         A[i] = A[j];
         A[j] = k;
         }

Step2: /* Obtain cycle lengths. */
       P = NIL;
       i = 1;
       do
         {
         h = 0;
         j = i;
         do
           {
           k = A[j];
           A[j] = -j;
           j = k;
           h = h + 1;
           }
         while (!(A[j] < 0));
         P = COMP(h,P);
         do
           i = i + 1;
         while (!(i > n || A[i] > 0));
         }
       while (!(i > n));

Step3: /* Sort. */
       P = LBIBMS(P);

Return: /* Prepare for return. */
       return(P);
}
