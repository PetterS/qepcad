/*======================================================================
                      d <- MPUCS(r,p,A,c)

Modular polynomial univariate content subroutine.

Inputs
  r : a BETA-digit, r >= 2.
  p : a BETA-digit, prime.
  A : in Z/(p)[X1,...,Xr], non-zero.
  c : in Z/(p)[X].

Outputs
  d : in Z/(p)[X], the g.c.d. of c and the univariate content of A.
======================================================================*/
#include "saclib.h"

Word MPUCS(r,p,A,c)
       Word r,p,A,c;
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
         if (rp == 1)
           d = MUPGCD(p,a,d);
         else
           d = MPUCS(rp,p,a,d);
         }
       while (!(Ap == NIL || PDEG(d) == 0));

Return: /* Prepare for return. */
       return(d);
}
