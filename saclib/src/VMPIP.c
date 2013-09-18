/*======================================================================
                      c <- VMPIP(r,m,A,B)

Vector of modular polynomial inner product.

Inputs
  A,B : vectors of polynomials in Z/(m)[X1,...,Xr].
  r   : a BETA-digit, r >= 0.
  m   : a BETA-digit.

Outputs
  c   : in Z, the inner product of A and B.
======================================================================*/
#include "saclib.h"

Word VMPIP(r,m,A,B)
       Word r,m,A,B;
{
       Word Ap,Bp,a,b,c;
       /* hide Ap,Bp,a,b; */

Step1: /* A=0 or B=0. */
       c = 0;
       if (A == 0 || B == 0)
         goto Return;

Step2: /* General case. */
       Ap = A;
       Bp = B;
       do
         {
         ADV(Ap,&a,&Ap);
         ADV(Bp,&b,&Bp);
         if (r == 0)
           c = MDSUM(m,c,MDPROD(m,a,b));
         else
           c = MPSUM(r,m,c,MPPROD(r,m,a,b));
         }
       while (!(Ap == NIL));

Return: /* Prepare for return. */
       return(c);
}
