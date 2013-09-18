/*======================================================================
                      B <- IPDER(r,A,i)

Integral polynomial derivative.

Inputs
  r : a BETA-digit, r >= 1, the number of variables.
  A : in Z[X1,...Xr].    
  i : in Z, 1 <= i <= r.

Outputs
  B  : in Z[X1,...Xr], the derivative of A with 
       respect to the i-th variable.
======================================================================*/
#include "saclib.h"

Word IPDER(r,A,i)
       Word r,A,i;
{
       Word Ap,B,a,b,e,rp;
       /* hide a,rp; */

Step1: /* A=0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* i=r. */
       if (i == r)
         {
         B = IPDMV(r,A);
         goto Return;
         }

Step3: /* i < r. */
       Ap = A;
       rp = r - 1;
       B = NIL;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         b = IPDER(rp,a,i);
         if (b != 0)
           B = COMP2(b,e,B);
         }
       while (!(Ap == NIL));
       B = INV(B);
       if (B == NIL)
         B = 0;

Return: /* Prepare for return. */
       return(B);
}
