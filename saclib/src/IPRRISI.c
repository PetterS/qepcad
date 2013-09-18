/*======================================================================
                      L <- IPRRISI(A,I)

Integral polynomial real root isolation in standard interval.

Inputs
  A  : in Z[X].
  I  : an open or one-point standard interval in logarithmic
       representation. All roots of A in I are simple.

Outputs
  L  : a list (I1,...,Ir) of isolating intervals for the real roots
       of A in I. Each interval is an open or one-point standard
       interval in logarithmic representation. Let (a_j,b_j) denote
       the endpoints of I_j.  Then a_1 <= b_1 <= ... <= a_r <= b_r.
======================================================================*/
#include "saclib.h"

Word IPRRISI(A,I)
       Word A,I;
{
       BDigit e,k;
       Word a,B,b,c,d,L;

Step1: /* Degree zero. */
       if (PDEG(A) == 0) {
         L = NIL;
         goto Return; }

Step2: /* One-point interval. */
       FIRST2(I,&a,&b);
       if (LBRNCOMP(a,b) == 0) {
         if (IUPBRES(A,a) == 0)
           L = LIST1(I);
         else
           L = NIL;
         goto Return; }

Step3: /* Transform A. */
       k = LSILW(I);
       if (a == 0)
         c = 0;
       else {
         FIRST2(a,&d,&e);
         c = IMP2(d,-k-e); }
       B = IUPBHT(A,k);
       B = IUPTR(B,c);

Step4: /* Compute roots. */
       L = IPRRISD(B,a,b);

Return: /* Prepare for return. */
       return(L);
}
