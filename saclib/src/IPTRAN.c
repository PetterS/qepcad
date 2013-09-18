/*======================================================================
                      B <- IPTRAN(r,A,T)

Integral polynomial translation.

Inputs
  A : in Z[X1,...,Xr].
  r : a BETA-digit, r >= 1, the number of variables.
  T : a list (tr,...,t1) of integers.

Outputs
  B : in Z[X1,...,Xr],   
      B(X1,...,Xr) = A(X1+t1,...,Xr+tr).
======================================================================*/
#include "saclib.h"

Word IPTRAN(r,A,T)
       Word r,A,T;
{
       Word B,Bp,Tp,b,bp,e,rp,t;
       /* hide rp; */

Step1: /* Translate main variable. */
       ADV(T,&t,&Tp);
       B = IPTRMV(r,A,t);

Step2: /* Translate coefficients. */
       rp = r - 1;
       if (rp == 0 || B == 0)
         goto Return;
       Bp = B;
       B = NIL;
       do
         {
         ADV2(Bp,&e,&bp,&Bp);
         b = IPTRAN(rp,bp,Tp);
         B = COMP2(b,e,B);
         }
       while (!(Bp == NIL));
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
