/*======================================================================
                      C <- MPUQ(r,p,A,b)

Modular polynomial univariate quotient.

Inputs
  A : in Z/(p)[X1,...,Xr].
  b : in Z/(p)[X1], non-zero divisor of A.
  r : a BETA-digit, r >= 2.
  p : a prime BETA-digit.

Outputs
  C :  in Z/(p)[X1,...,Xr], C(X1,...,Xr) = A(X1,...,Xr) / b(X1).
======================================================================*/
#include "saclib.h"

Word MPUQ(r,p,A,b)
       Word r,p,A,b;
{
       Word Ap,C,a,c,e,rp;
       /* hide a,rp; */

Step1: /* A=0. */
       if (A == 0)
         {
         C = 0;
         goto Return;
         }

Step2: /* A non-zero. */
       Ap = A;
       rp = r - 1;
       C = NIL;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         if (rp == 1)
           c = MPQ(rp,p,a,b);
         else
           c = MPUQ(rp,p,a,b);
         C = COMP2(c,e,C);
         }
       while (!(Ap == NIL));
       C = INV(C);

Return: /* Prepare for return. */
       return(C);
}
