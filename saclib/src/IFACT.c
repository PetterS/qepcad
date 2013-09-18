/*======================================================================
                      F <- IFACT(n)

Integer factorization.

Inputs
  n  : a positive integer.

Outputs
  F  : the ordered list (q1, q2,...,qh) of the prime factors of n,
       with n equal to the product of qi.
======================================================================*/
#include "saclib.h"

Word IFACT(n)
       Word n;
{
       Word F,Fp,a,b,c,m,mp,p,r,s,t;
       /* hide s,t; */

Step1: /* Find small factors of n. */
       ISPD(n,&F,&m);
       if (m == 1)
         goto Return;
       F = INV(F);
       a = 1000;

Step2: /* Test for primality. */
       if (m < BETA)
         {
         mp = m - 1;
         r = MDEXP(m,3,mp);
         }
       else
         {
         mp = IDIF(m,1);
         r = MIEXP(m,3,mp);
         }
       if (r == 1)
         goto Step5;

Step3: /* Search for a medium divisor. */
       ISQRT(m,&c,&t);
       b = IMAX(5000,IDQ(c,3));
       if (ICOMP(a,b) > 0)
         goto Step4;
       IMPDS(m,a,b,&p,&m);
       if (p != 1)
         {
         a = p;
         F = COMP(p,F);
         goto Step2;
         }
       a = b;

Step4: /* Search for large divisor. */
       b = c;
       ILPDS(m,a,b,&p,&m);
       if (p != 1)
         F = COMP(p,F);
       F = COMP(m,F);
       F = INV(F);
       goto Return;

Step5: /* Selfridge primality test. */
       Fp = IFACT(mp);
       s = ISPT(m,mp,Fp);
       if (s == 1)
         {
         F = COMP(m,F);
         F = INV(F);
         goto Return;
         }
       goto Step3;

Return: /* Prepare for return. */
       return(F);
}
