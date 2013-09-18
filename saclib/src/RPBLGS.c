/*======================================================================
                      RPBLGS(r,A; a,b,s)

Rational polynomial base coefficients least common multiple,
greatest common divisor, and sign.

Inputs
  r : a BETA-digit, r >= 0.
  A : in Q[X1,...,Xr].

Outputs
  a : in Z, the lcm of the denominators of the base coefficients of A.
      If A = 0 then a = 0.
  b : in Z, the gcd of the numerators of the base coefficients of A.
      If A = 0 then b = 0.
  s : a BETA-digit, the sign of the leading base coefficient of A. 
      If A = 0 then s = 0.
======================================================================*/
#include "saclib.h"

void RPBLGS(r,A, a_,b_,s_)
       Word r,A, *a_,*b_,*s_;
{
       Word As,a,ap,b,bp,c,e,rp,s,sp;
       /* hide e,rp,s,sp; */

Step1: /* A = 0. */
       if (A == 0)
         {
         a = 0;
         b = 0;
         s = 0;
         goto Return;
         }

Step2: /* r = 0. */
       if (r == 0)
         {
         bp = FIRST(A);
         s = ISIGNF(bp);
         b = IABSF(bp);
         a = SECOND(A);
         goto Return;
         }

Step3: /* General case. */
       rp = r - 1;
       ADV2(A,&e,&c,&As);
       RPBLGS(rp,c,&a,&b,&s);
       while (As != NIL)
         {
         ADV2(As,&e,&c,&As);
         if (rp == 0)
           FIRST2(c,&bp,&ap);
         else
           RPBLGS(rp,c,&ap,&bp,&sp);
         a = ILCM(a,ap);
         if (b != 1)
           b = IGCD(b,bp);
         }

Return: /* Prepare for return. */
       *a_ = a;
       *b_ = b;
       *s_ = s;
       return;
}
