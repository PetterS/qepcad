/*======================================================================
                           b <- SNLBRN(a,k)

Small nearby logarithmic binary rational number.

Inputs
   a : a logarithmic binary rational number.
   k : a beta digit.

Output
   b :  a logarithmic binary rational number.  Let b' be the
        integral part of 2^k * b.  Then b = b' / 2^k.  If
        a >= 0, b is the largest multiple of 1 / 2^k that is
        less than or equal to a.  If a < 0, b is the least
        multiple of 1 / 2^k that is greater then or equal
        to a.
======================================================================*/
#include "saclib.h"

Word SNLBRN(a,k)
        Word a;
        BDigit k;
{
        BDigit h;
        Word ap,b,bp;

Step1: /* Compute b', the integral part of 2^k * a. */
        if (a == 0)
           bp = 0;
        else {
           FIRST2(a,&ap,&h);
           if (h - k >= 0) 
              bp = IDP2(ap,h - k);
           else
              bp = IMP2(ap,k - h); }

Step2: /* Compute b = b' / 2^k. */
        b = LBRNFIE(bp,- k);

Return: /* Return b. */
        return(b);
}
