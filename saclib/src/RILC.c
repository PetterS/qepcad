/*======================================================================
                      t <- RILC(I,k)

Rational interval length comparison.

Inputs
  I : an interval (a,b) with rational endpoints, a <= b.
  k : a Gammma-integer.

Outputs
  t : a BETA-digit, t = 1 if b-a <= 2^k and t = 0 otherwise.
======================================================================*/
#include "saclib.h"

Word RILC(I,k)
       Word I,k;
{
       Word a,b,d,m,n,t;
       /* hide a,b,m,n,t; */

Step1: /* Compare. */
       FIRST2(I,&a,&b);
       d = RNDIF(b,a);
       t = 1;
       if (d != 0)
         {
         RNFCL2(d,&m,&n);
         if (n > k)
           t = 0;
         }

Return: /* Prepare for return. */
       return(t);
}
