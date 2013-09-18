/*======================================================================
                      d <- IPICS(r,A,c)

Integral polynomial integer content subroutine.

Inputs
  r : a BETA-digit, r > 0.
  A : in Z[X1,...,Xr], non-zero.
  c : in Z.

Outputs
  d : in Z, the g.c.d. of c and the integer content of A.
======================================================================*/
#include "saclib.h"

Word IPICS(r,A,c)
       Word r,A,c;
{
       Word Ap,a,d,e,rp;
       /* hide a,e,rp; */

Step1: /* Compute. */
       Ap = A;
       rp = r - 1;
       d = c;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         if (rp == 0)
           d = IGCD(a,d);
         else
           d = IPICS(rp,a,d);
         if (d == 1)
           goto Return;
         }
       while (!(Ap == NIL));

Return: /* Prepare for return. */
       return(d);
}
