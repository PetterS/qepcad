/*======================================================================
                      B <- ISPSFB(r,A)

Integral squarefree polynomial squarefree basis.

Inputs
  r : a BETA-digit, r > 0.
  A : a list of positive primitive squarefree polynomials in Z[X1,...,Xr],
      each of which is of positive degree in its main variable.

Outputs
  B : a list of polynomials in Z[X1,...,Xr], a coarsest squarefree 
      basis for A.
======================================================================*/
#include "saclib.h"

Word ISPSFB(r,A)
       Word r,A;
{
       Word A1,Ap,B;
       /* hide A1,Ap; */

Step1: /* Compute. */
       B = NIL;
       Ap = A;
       while (Ap != NIL)
         {
         ADV(Ap,&A1,&Ap);
         B = IPSFBA(r,A1,B);
         }

Return: /* Prepare for return. */
       return(B);
}
