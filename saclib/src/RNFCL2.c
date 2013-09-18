/*======================================================================
                      RNFCL2(a; m,n)

Rational number floor and ceiling of logarithm, base 2.  

Inputs
  a : a non-zero rational number, not necessarily reduced.

Outputs
  m : a BETA-digit, m = floor(log2(abs(a))).
  n : a BETA-digit, n = ceiling(log2(abs(a))).
======================================================================*/
#include "saclib.h"

void RNFCL2(a, m_,n_)
       Word a, *m_,*n_;
{
       Word a1,a2,ap1,c,d,m,m1,m2,n,n1,n2,s;
       /* hide a1,a2,d,m,m1,m2,n,n1,n2,s; */

Step1: /* Apply IFCL2 to numerator and denominator. */
       FIRST2(a,&a1,&a2);
       IFCL2(a1,&m1,&n1);
       IFCL2(a2,&m2,&n2);
       m = m1 - n2;
       n = n1 - m2;

Step2: /* n <= m+1. */
       if (n <= m + 1)
         goto Return;

Step3: /* Resolve uncertainty. */
       ap1 = IABSF(a1);
       if (m + 1 >= 0)
         {
         c = ap1;
         d = IMP2(a2,m + 1);
         }
       else
         {
         c = IMP2(ap1,-m - 1);
         d = a2;
         }
       s = ICOMP(c,d);
       if (s < 0)
         n = n - 1;
       else
         m = m + 1;

Return: /* Prepare for return. */
       *m_ = m;
       *n_ = n;
       return;
}
