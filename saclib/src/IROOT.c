/*======================================================================
                      IROOT(A,n; B,t)

Integer root.  

Inputs
  A : in Z. A > 0.
  n : BETA-integer. n >= 2. 

Outputs
  B : floor(A^(1/n)).
  t : sign(A-B^n).
======================================================================*/
#include "saclib.h"

void IROOT(A,n, B_,t_)
       Word A,n, *B_,*t_;
{
       Word Ap,B,Bp,C,D,E,F,R,h,k,np,r,s,t,u;
       /* hide h,k,np,r,s,t,u; */

Step1: /* Compute first approximation. */
       k = ILOG2(A);
       np = n - 1;
       h = k / n;
       r = k - h * n;
       u = (4 * r) / n;
       if (h >= 2)
         B = IMP2(u + 5,h - 2);
       else
         B = 4;

Step2: /* Iterate modified newton method. */
       do
         {
         C = IEXP(B,np);
         IQR(A,C,&D,&R);
         s = ICOMP(B,D);
         if (s <= 0)
           goto Step3;
         else
           {
           E = IDPR(B,np);
           F = ISUM(E,D);
           B = IDQ(F,n);
           }
         }
       while (1);

Step3: /* Test whether result is too small. */
       if (s == 0)
         t = ISIGNF(R);
       else
         {
         Bp = ISUM(B,1);
         Ap = IEXP(Bp,n);
         t = ICOMP(A,Ap);
         if (t >= 0)
           B = Bp;
         else
           t = 1;
         }

Return: /* Prepare for return. */
       *B_ = B;
       *t_ = t;
       return;
}
