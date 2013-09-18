/*======================================================================
                      B <- DPFP(r,A)

Dense polynomial from polynomial. 

Inputs
  r : a BETA-digit, r >= 0, the number of variables.
  A : in Z[X1,...,Xr].

Outputs
  B : the result of converting A to dense polynomial representation.
======================================================================*/
#include "saclib.h"

Word DPFP(r,A)
       Word r,A;
{
       Word Ap,B,b,k,n,rp;
       /* hide k,n,rp; */

Step1: /* Convert. */
       if (A == 0 || r == 0)
         {
         B = A;
         goto Return;
         }
       n = PDEG(A);
       rp = r - 1;
       B = NIL;
       Ap = A;
       for (k = n; k >= 0; k--)
         {
         if (Ap == NIL || FIRST(Ap) < k)
           b = 0;
         else
           {
           Ap = RED(Ap);
           ADV(Ap,&b,&Ap);
           if (rp > 0)
             b = DPFP(rp,b);
           }
         B = COMP(b,B);
         }
       B = COMP(n,INV(B));

Return: /* Prepare for return. */
       return(B);
}
