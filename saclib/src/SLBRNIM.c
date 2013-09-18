/*======================================================================
                           c <- SLBRNIM(a,b)

Small logarithmic binary rational near interval midpoint.

Inputs
   a, b : logarithmic binary rational numbers, a < b.

Output
   c :  a logarithmic binary rational number.  Let d = b - a
        and k = floor(log_2 d).  Then c is one of the two 
        integral multiples of 1 / 2^{k - 3} that are nearest
        to the midpoint of [a,b].  It follows that c - a
        and b - c are both >= 3/8 * d.
======================================================================*/
#include "saclib.h"

Word SLBRNIM(a,b)
        Word a,b;
{
        BDigit h,k;
        Word c,cp,d,dp;

Step1: /* Compute k. */
        d = LBRNDIF(b,a);
        FIRST2(d,&dp,&h);
        k = ILOG2(dp) - h - 1;

Step2: /* Compute c', the midpoint. */
        cp = LBRIMID(LIST2(a,b));

Step3: /* Compute c. */
        c = SNLBRN(cp,- k + 3);

Return: /* Return c. */
        return(c);
}
