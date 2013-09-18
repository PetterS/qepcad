/*======================================================================
                      DQR(a1,a0,b; q,r)

Digit quotient and remainder.  

Inputs
  a1, a0, b : BETA-integers with a1 * a0 >= 0 and abs(b) > abs(a1).  

Outputs
  q : a BETA-integer, the integral part of (a1 * BETA + a0) / b.
  r : a BETA-integer, (a1 * BETA + a0) - b * q.  
======================================================================*/
#include "saclib.h"

void DQR(a1,a0,b, q_,r_)
       Word a1,a0,b, *q_,*r_;
{
       Word ap0,ap1,bp,i,q,qp,r;
       /* hide algorithm */

Step1: /* a1 = 0. */
       if (a1 == 0)
         {
         QREM(a0,b,&q,&r);
         goto Return;
         }

Step2: /* Compute absolute values. */
       ap1 = ABS(a1);
       ap0 = ABS(a0);
       bp = ABS(b);

Step3: /* Shift and subtract. */
       qp = 0;
       for (i = 1; i <= ZETA; i++)
         {
         ap1 = ap1 + ap1;
         ap0 = ap0 + ap0;
         if (ap0 >= BETA)
           {
           ap0 = ap0 - BETA;
           ap1 = ap1 + 1;
           }
         qp = qp + qp;
         if (ap1 >= bp)
           {
           ap1 = ap1 - bp;
           qp = qp + 1;
           }
         }

Step4: /* Compute signs. */
       if (a1 < 0)
         {
         qp = -qp;
         ap1 = -ap1;
         }
       if (b < 0)
         qp = -qp;
       q = qp;
       r = ap1;

Return: /* Prepare for return. */
       *q_ = q;
       *r_ = r;
       return;
}
