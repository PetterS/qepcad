/*======================================================================
                      B <- VIAZ(A,n)

Vector of integers, adjoin zeros.

Inputs
  A : an m-vector over Z.
  n : a BETA-digit, n > 0.

Outputs
  B : an (m+n)-vector over Z, B = (a1,...,am,0,...,0).

Remarks:
  A is modified.
======================================================================*/
#include "saclib.h"

Word VIAZ(A,n)
       Word A,n;
{
       Word B,k;
       /* hide k; */

Step1: /* Compute. */
       B = NIL;
       for (k = 1; k <= n; k++)
         B = COMP(0,B);
       B = CONC(A,B);

Return: /* Prepare for return. */
       return(B);
}
