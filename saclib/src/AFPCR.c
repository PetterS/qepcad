/*======================================================================
                      B <- AFPCR(r,A)

Algebraic number field polynomial convert representation.

Inputs
  r : a BETA-digit, r >= 1, the number of variables.
  A : in Q(alpha)[X1,...,Xr] represented as an element of
      Q[x,X1,...,Xr].

Outputs
  B : in Q(alpha)[X1,...,Xr], where the coefficients of A are
      represented as (ai,Ai), where ai is in Q and Ai is in Z[x].
======================================================================*/
#include "saclib.h"

Word AFPCR(r,A)
       Word r,A;
{
       Word Ap,B,a,b,e,rp;
       /* hide rp; */

Step1: /* A equal 0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* A not equal 0. */
       rp = r - 1;
       Ap = A;
       B = NIL;
       while (Ap != NIL)
         {
         ADV2(Ap,&e,&a,&Ap);
         if (rp == 0)
           b = AFCR(a);
         else
           b = AFPCR(rp,a);
         B = COMP2(b,e,B);
         }
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
