/*======================================================================
                      t <- RIB(r,s)

Rational interval bisection.

Inputs
  r,s : binary rational numbers, r < s. 

Outputs
  t : a binary rational number with r < t < s, defined as follows.
      Let h = floor(log2(s-r)) and let c be the least integer
      such that c * 2^h > r.  Then t = c2^h if c2^h < s and
      t = (2c-1)2^(h-1) otherwise.
======================================================================*/
#include "saclib.h"

Word RIB(r,s)
       Word r,s;
{
       Word H,c,d,e,h,hp,n,q,t;
       /* hide e,h,n; */

Step1: /* Compute h'=2^h. */
       d = RNDIF(r,s);
       RNFCL2(d,&h,&n);
       hp = RNP2(h);

Step2: /* Compute t. */
       q = RNQ(r,hp);
       c = RNCEIL(q);
       c = RNINT(c);
       t = RNPROD(c,hp);
       e = RNCOMP(t,r);
       if (e == 0)
         t = RNSUM(t,hp);
       e = RNCOMP(t,s);
       if (e >= 0)
         {
         H = LIST2(1,2);
         hp = RNPROD(hp,H);
         t = RNDIF(t,hp);
         }

Return: /* Prepare for return. */
       return(t);
}
