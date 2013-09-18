/*======================================================================
                      b <- IUPBRE(A,a)

Integral univariate polynomial binary rational evaluation.

Inputs
  A : in Z[X].
  a : binary rational number.

Outputs
  b : in Q, the binary rational number A(a).
======================================================================*/
#include "saclib.h"

Word IUPBRE(A,a)
       Word A,a;
{
       Word b,b1,b2,c,d,h,k,m,n;
       /* hide b,c,d,h,k,m,n; */

Step1: /* A=0. */
       b = 0;
       if (A == 0)
         goto Return;

Step2: /* A /= 0. */
       if (a == 0)
         {
         c = 0;
         m = 0;
         }
       else
         {
         FIRST2(a,&c,&d);
         m = IORD2(d);
         }
       b1 = IUPBEI(A,c,m);
       if (b1 == 0)
         goto Return;
       k = IORD2(b1);
       n = FIRST(A);
       h = m * n;
       if (k >= h)
         {
         b1 = ITRUNC(b1,h);
         b2 = 1;
         }
       else
         {
         b1 = ITRUNC(b1,k);
         h = h - k;
         b2 = IMP2(1,h);
         }
       b = LIST2(b1,b2);

Return: /* Prepare for return. */
       return(b);
}
