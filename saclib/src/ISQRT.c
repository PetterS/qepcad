/*======================================================================
                      ISQRT(A; B,t)

Integer square root.  

Inputs
  A : in Z. A >= 0.

Outputs
  B : the floor function of the square root of A.
  t : the sign of A - B * B.
======================================================================*/
#include "saclib.h"

void ISQRT(A, B_,t_)
       Word A, *B_,*t_;
{
       Word B,C,D,R,a,b,h,k,s,t;
       /* hide a,b,h,k,s,t; */

Step1: /* A single-precision. */
       if (A < BETA)
         {
         DSQRTF(A,&B,&t);
         goto Return;
         }

Step2: /* Compute single-precision approximation. */
       k = ILOG2(A);
       h = k - ZETA;
       h = h + ODD(h);
       a = IDP2(A,h);
       DSQRTF(a,&b,&t);
       b = b + 1;
       B = IMP2(b,h / 2);

Step3: /* Iterate modified newton method. */
       do
         {
         IQR(A,B,&C,&R);
         s = ICOMP(B,C);
         if (s <= 0)
           goto Step4;
         D = ISUM(B,C);
         B = IDQ(D,2);
         }
       while (1);

Step4: /* Compute t. */
       if (R == 0 && s == 0) 
         t = 0;
       else
         t = 1;

Return: /* Prepare for return. */
       *B_ = B;
       *t_ = t;
       return;
}


