/*======================================================================
                      DSQRTF(a; b,t)

Digit square root function.

Inputs
  a  : non-negative BETA-digit.

Outputs
  b  : the floor function of the square root of a.
  t  : the sign of a-b*b.
======================================================================*/
#include "saclib.h"

void DSQRTF(a, b_,t_)
       Word a, *b_,*t_;
{
       Word b,c,h,k,r,t;
       /* hide algorithm */

Step1: /* a=0. */
       if (a == 0)
         {
         b = 0;
         t = 0;
         goto Return;
         }

Step2: /* Compute first approximation. */
       k = DLOG2(a);
       h = (k + 1) / 2;
       b = TABP2[h + 1];

Step3: /* Iterate modified Newton method. */
       do
         {
         QREM(a,b,&c,&r);
         if (b <= c)
           {
           t = SIGN(a - b * b);
           goto Return;
           }
         b = (b + c) / 2;
         }
       while (1);

Return: /* Prepare for return. */
       *b_ = b;
       *t_ = t;
       return;
}
