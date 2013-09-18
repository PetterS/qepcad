/*========================================================================
                        L <- IUPRRAFE(A,E,k)

Integral univariate polynomial real root approximation from estimates.

Inputs
   A:  a squarefree integral univariate polynomial of positive degree.
   E:  a list (a_1,a_2,...,a_r) of logarithmic binary rational numbers
       such that r > 0 is knon to be the number of real roots of A
       and a_i is an estimate of the i-th real root of A.
   k:  an integer.

Output
   L:  a list (b_1,b_2,...,b_r) of logarithmic binary rational numbers 
       such that the i-th real root of A is either b_i or is in the 
       open interval (b_i,b_i + 2^{-k}).
========================================================================*/
#include "saclib.h"

Word IUPRRAFE(A,E,k)
        Word A,E,k;
{
        Word a,b,bp,i,I,L,L1,n,s,t,u;

Step1: /* Initialize s to the sign of A at minus infinity. */
        s = ISIGNF(PLDCF(A));
        n = PDEG(A);
        if (IODD(n))
           s = -s;

Step2: /*  Form the logarithmic binary rational number I = 2^{-k}. */
        I = LIST2(1,k);

Step3: /* Initialize output list L. */
        L = NIL;
        
Step4: /* Evaluate the sign of A at an approximation a; if zero,
set b = a and go to Step7. */

        ADV(E,&a,&E);
        t = IUPBRES(A,a);
        if (t == 0) {
           b = a;
           goto Step7; }

Step5: /* Add or subtract 2^{-k} to approximation until the opposite
sign, or zero, is obtained for A, but no more than 3 times.  If
3 times does not suffice, go to Step 10. */

        i = 0;
        while (i < 3) {
           i = i + 1;
           if (t == s)
              a = LBRNSUM(a,I);
           else
              a = LBRNDIF(a,I);
           u = IUPBRES(A,a);
           if (u != t || u == 0)
              goto Step6; }
        goto Step10;

Step6: /* Choose the left endpoint of an isolating interval (or the
root itself) as the aproximation b. */

        if (u == 0)
           b = a;
        else if (t == s)
           b = LBRNDIF(a,I);
        else
           b = a;

Step7: /* Check whether b is greater then the approximation for
the preceding root, if any.  If not, then go to Step 10. */

        if (L != NIL) {
           bp = FIRST(L);
           if (LBRNCOMP(b,bp) <= 0)
              goto Step10; }

Step8: /* Prefix b to the list L, change the sign of s, and return 
for the next root, if any.  (s will always be the sign of A just to
the left of the next root of A.) */

        L = COMP(b,L);
        s = -s;
        if (E != NIL)
           goto Step4;

Step9: /* Invert the list L and return. */

        L = INV(L);
        goto Return;

Step10: /*  Disjoint isolating intervals were not found; use root 
isolation and refinement.  Then extract the left endpoints of the 
isolating intervals. */

        L = IPRRIRDB(A,-k);
        L1 = NIL;
        while (L != NIL) {
           ADV(L,&I,&L);
           a = FIRST(I);
           L1 = COMP(a,L1); }
        L = INV(L1);

Return: /* Return the list L. */
        return(L);
}
