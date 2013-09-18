/*======================================================================
                      B <- MPEMV(r,m,A,a)

Modular polynomial evaluation of main variable.

Inputs
  A : in Z/(m)[X1,...,Xr].
  r : a BETA-digit, r >= 1, the number of variables.
  m : a BETA-digit.
  a : in Z/(m).

Outputs
  B : in Z/(m)[X1,...,X_{r-1}],
      B(X1,...,X_{r-1})=A(X1,...,X_{r-1},a).
======================================================================*/
#include "saclib.h"

Word MPEMV(r,m,A,a)
       Word r,m,A,a;
{
       Word Ap,B,a1,e1,e2,i,rp;
       /* hide Ap,a1,e1,e2,i,rp; */

Step1: /* A=0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* Apply Horners method. */
       ADV(A,&e1,&Ap);
       B = 0;
       rp = r - 1;
       do
         {
         ADV(Ap,&a1,&Ap);
         if (rp == 0)
           B = MDSUM(m,B,a1);
         else
           B = MPSUM(rp,m,B,a1);
         if (Ap != NIL)
           ADV(Ap,&e2,&Ap);
         else
           e2 = 0;
         for (i = 1; i <= e1 - e2; i++)
           if (rp == 0)
             B = MDPROD(m,a,B);
           else
             B = MPMDP(rp,m,a,B);
         e1 = e2;
         }
       while (!(Ap == NIL));

Return: /* Prepare for return. */
       return(B);
}
