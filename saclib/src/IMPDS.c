/*======================================================================
                      IMPDS(n,a,b; p,q)

Integer medium prime divisor search. 

Inputs
  n,a,b : in Z.  n,a,b > 0.  a <= b <= n. 
          n has no positive divisors less than a.

Outputs
  p, q  : If n has a prime divisor in the closed interval from a to b 
          then p is the least such prime and q=n/p.  
          Otherwise p=1 and q=n.
======================================================================*/
#include "saclib.h"

void IMPDS(n,a,b, p_,q_)
       Word n,a,b, *p_,*q_;
{
       Word Lp,p,pp,q,r,r1,r2;
       /* hide Lp,pp,r,r1,r2; */

Step1: /* Determine first divisor. */
       r = IDREM(a,210);
       Lp = UZ210;
       while (r > FIRST(Lp))
         Lp = RED(Lp);
       r1 = FIRST(Lp);
       p = ISUM(a,r1 - r);

Step2: /* Repeated trial division. */
       while (ICOMP(p,b) <= 0)
         {
         if (p < BETA)
           IDQR(n,p,&q,&r);
         else
           IQR(n,p,&q,&r);
         if (r == 0)
           goto Return;
         Lp = RED(Lp);
         if (Lp == NIL)
           {
           Lp = UZ210;
           r2 = r1 - 210;
           }
         else
           r2 = r1;
         r1 = FIRST(Lp);
         if (p < BETA)
           {
           pp = p + r1 - r2;
           if (pp >= BETA)
             p = LIST2(pp - BETA,1);
           else
             p = pp;
           }
         else
           p = ISUM(p,r1 - r2);
         }

Step3: /* No divisors found. */
       p = 1;
       q = n;

Return: /* Prepare for return. */
       *p_ = p;
       *q_ = q;
       return;
}
