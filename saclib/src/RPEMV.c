/*======================================================================
                      C <- RPEMV(r,A,b)

Rational polynomial evaluation, main variable.

Inputs
  A : in Q[X1,...,Xr].
  r : a BETA-digit, r >= 1.
  b : in Q.

Outputs
  C : in Q[X1,...,X_{r-1}], C(X1,...,X_{r-1}) = A(X1,...,X_{r-1},b).
======================================================================*/
#include "saclib.h"

Word RPEMV(r,A,b)
       Word r,A,b;
{
       Word Ap,C,a,e,ep,i,rp;
       /* hide Ap,a,e,ep,i,rp; */

Step1: /* A=0. */
       if (A == 0)
         {
         C = 0;
         goto Return;
         }

Step2: /* Horner method. */
       Ap = A;
       C = 0;
       rp = r - 1;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         if (Ap == NIL)
           ep = 0;
         else
           ep = FIRST(Ap);
         C = RPSUM(rp,C,a);
         for (i = 1; i <= e - ep; i++)
           C = RPRNP(rp,b,C);
         }
       while (!(Ap == NIL));

Return: /* Prepare for return. */
       return(C);
}
