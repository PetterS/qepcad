/*======================================================================
                      b <- PUNT(r,A)

Polynomial univariate test.

Inputs
  A : in R[X1,...,Xr], R ring.
  r : a BETA-digit, r >= 1.

Outputs
  b : integer, b = 2 if A has degree zero in all variables.
      b = 1 if A has degree zero in X2,...,Xr, but positive degree in X1.
      Otherwise b = 0.
======================================================================*/
#include "saclib.h"

Word PUNT(r,A)
       Word r,A;
{
       Word Ap,b,i;
       /* hide b,i; */

Step1: /* A = 0. */
       b = 2;
       if (A == 0)
         goto Return;

Step2: /* A /= 0. */
       Ap = A;
       for (i = 1; i <= r - 1; i++)
         {
         if (PDEG(Ap) != 0)
           {
           b = 0;
           goto Return;
           }
         else
           Ap = PLDCF(Ap);
         }
       if (PDEG(Ap) > 0)
         b = 1;

Return: /* Prepare for return. */
       return(b);
}
