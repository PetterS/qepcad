/*======================================================================
                      b <- PCONST(r,A)

Polynomial constant.

Inputs
  A : a polynomial in r variables.
  r : a BETA-digit,r >= 1.

Outputs
  b : integer, b = 1 if A is a constant polynomial, otherwise b = 0.
======================================================================*/
#include "saclib.h"

Word PCONST(r,A)
       Word r,A;
{
       Word Ap,b,i;
       /* hide algorithm */

Step1: /* A = 0. */
       b = 1;
       if (A == 0)
         goto Return;

Step2: /* A /= 0. */
       Ap = A;
       for (i = 1; i <= r; i++)
         {
         if (PDEG(Ap) != 0)
           {
           b = 0;
           goto Return;
           }
         else
           Ap = PLDCF(Ap);
         }

Return: /* Prepare for return. */
       return(b);
}
