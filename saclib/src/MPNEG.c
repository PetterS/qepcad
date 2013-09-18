/*======================================================================
                      B <- MPNEG(r,m,A)

Modular polynomial negative.

Inputs
  A : in Z/(m)[X1,...,Xr].
  r : a BETA-digit, r >= 1, the number of variables.
  m : a BETA-digit.

Outputs
  B :  in Z/(m)[X1,...,Xr], B = -A.
======================================================================*/
#include "saclib.h"

Word MPNEG(r,m,A)
       Word r,m,A;
{
       Word Ap,B,a,b,e,rp;
       /* hide a,rp; */

Step1: /* A=0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* A non-zero. */
       Ap = A;
       B = NIL;
       rp = r - 1;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         if (rp == 0)
           b = MDNEG(m,a);
         else
           b = MPNEG(rp,m,a);
         B = COMP2(b,e,B);
         }
       while (!(Ap == NIL));
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
