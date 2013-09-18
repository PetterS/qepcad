/*======================================================================
                      B <- PFDP(r,A)

Polynomial from dense polynomial.

Inputs
  A : in R[X1,...,Xr], dense representation. 
  r : a BETA-digit, r >= 0.

Outputs
  B : in R[X1,...,Xr], the result of converting A to recursive 
      representation.
======================================================================*/
#include "saclib.h"

Word PFDP(r,A)
       Word r,A;
{
       Word Ap,B,b,n,rp;
       /* hide rp; */

Step1: /* Convert. */
       if (A == 0 || r == 0)
         {
         B = A;
         goto Return;
         }
       ADV(A,&n,&Ap);
       B = NIL;
       rp = r - 1;
       do
         {
         ADV(Ap,&b,&Ap);
         if (b != 0)
           {
           if (rp != 0)
             b = PFDP(rp,b);
           B = COMP2(b,n,B);
           }
         n = n - 1;
         }
       while (!(Ap == NIL));
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
