/*======================================================================
                      Is <- IPRRRI(A,B,I,s1,t1)

Integral polynomial relative real root isolation.

Inputs
  A, B  : in Z[X].
  I     : a left-open, right-closed interval (a1,a2) where a1 and a2 are
          binary rational numbers with a1 < a2.  A and B have unique roots,
          alpha and beta respectively, in I, each of odd multiplicity and
          with alpha /= beta.
  s1,t1 : BETA-digits, s1 = sign(A(a_1 +)) and t1 = sign(B(a_1 +)).

Outputs
  Is    : a left-open, right-closed subinterval of I, Is = (as1, as2) with
          as1 and as2 binary rational numbers and as1 < as2, such that
          Is contains alpha but not beta.
======================================================================*/
#include "saclib.h"

Word IPRRRI(A,B,I,s1,t1)
       Word A,B,I,s1,t1;
{
       Word Is,a,as1,as2,s,t,u,v;
       /* hide s,t,u,v; */

Step1: /* Initialize. */
       FIRST2(I,&as1,&as2);

Step2: /* Bisect. */
       a = RIB(as1,as2);
       s = IUPBES(A,a);
       if (s == 0)
         s = -s1;
       t = IUPBES(B,a);
       if (t == 0)
         t = -t1;
       u = s1 * s;
       v = t1 * t;
       if (u > 0)
         as1 = a;
       else
         as2 = a;
       if (u == v)
         goto Step2;

Step3: /* Construct I*. */
       Is = LIST2(as1,as2);

Return: /* Prepare for return. */
       return(Is);
}
