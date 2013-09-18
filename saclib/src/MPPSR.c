/*======================================================================
                      C <- MPPSR(r,p,A,B)

Modular polynomial pseudo-remainder.

Inputs
  A,B : in Z/(p)[X1,...,Xr], B non-zero.
  r : a BETA-digit, r >= 1, the number of variables.
  p : a prime BETA-digit.

Outputs
  C : in Z/(p)[X1,...,Xr], the pseudoremainder of A and B.
======================================================================*/
#include "saclib.h"

Word MPPSR(r,p,A,B)
       Word r,p,A,B;
{
       Word B1,Bb,Bs,C,C1,c,i,l,m,n;
       /* hide Bb,i,l,m,n; */

Step1: /* Deg(B)=0. */
       n = PDEG(B);
       if (n == 0)
         {
         C = 0;
         goto Return;
         }

Step2: /* Deg(B) > 0. */
       m = PDEG(A);
       C = A;
       Bb = PRED(B);
       B1 = LIST2(0,PLDCF(B));
       for (i = m; i >= n; i--)
         {
         if (C == 0)
           goto Return;
         l = PDEG(C);
         if (l == i)
           {
           c = PLDCF(C);
           C = PRED(C);
           C = MPPROD(r,p,C,B1);
           C1 = LIST2(l - n,c);
           Bs = MPPROD(r,p,Bb,C1);
           C = MPDIF(r,p,C,Bs);
           }
         else
           C = MPPROD(r,p,C,B1);
         }

Return: /* Prepare for return. */
       return(C);
}
