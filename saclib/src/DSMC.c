/*===========================================================================
                             r <- DSMC(m,mp,u)

Digit solution of modular congruence.

Inputs
  m,u : BETA-digits, m > 1, m odd, m > u >= 0.
  mp  : a BETA-digit, mp = floor((m/2)^(1/2)).

Outputs
  r : if u = 0 then r = 0.  Otherwise, if there exist integers 
      a > 0 and b /= 0 such that |a|, b < (m/2)^(1/2) and
      a = b u (mod m) then r = (a,b), but if not then r = NIL.
===========================================================================*/
#include "saclib.h"

Word DSMC(m,mp,u)
       Word m,mp,u;
{
       Word u0,u1,b0,b1,r,q,s;

Step1: /* u = 0. */
       if (u == 0) {
          r = 0;
          goto Return; }

Step2: /* Initialize. */
       if (2*u > m) {
          u1 = m - u;
          s = -1; }
       else {
          u1 = u;
          s = 1; }
       u0 = m;
       b0 = 0;
       b1 = 1;

Step3: /* Compute remainders and cosequence. */
       do {
          if (ABS(b1) > mp) {
             r = NIL;
             goto Return; }
          if (u1 <= mp) {
             if (u1 == 0) 
                r = NIL;
             else {
                if (b1 < 0) {
                   u1 = -u1;
                   b1 = -b1; }
                if (s == -1)
                   u1 = -u1;
                r = LIST2(u1,b1); }
             goto Return; }
          QREM(u0,u1,&q,&r);
          u0 = u1;
          u1 = r;
          r = b1;
          b1 = b0 - q * b1;
          b0 = r; }
       while(1);

Return: /* Prepare for return. */
       return(r);
}
