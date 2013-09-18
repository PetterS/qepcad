/*======================================================================
                      t <- IPFZT(r,A)

Integral polynomial finitely many common zeros test.
A = (A_1,...,A_n), n >= 1, is a list of nonzero integral
polynomials in r variables, r >= 1. T = 1 if it has been 
determined that the polynomials in A have only finitely many 
common zeros.  T = 0 if either it has not been determined how 
many common zeros the polynomials in A have, or if it has been 
determined that they have infinitely many common zeros.
======================================================================*/
#include "qepcad.h"

Word QepcadCls::IPFZT(Word r, Word A)
{
       Word A1,Ap,As,P,Ths,i,s,t;
       /* hide Ap,Ths,i,s,t; */

Step1: /* Initialize. */
                                /*Int*/ if (PCIPFZT == 'n') return(0);
                                /*Int*/ Ths = ACLOCK();
        t = 1; P = NIL; for (i = r; i >= 1; i--)
        P = COMP(i,P); i = 1;

Step2: /* Test for finitely many distinct x sub i - coordinates among
     the common zeros. */ Ap = A; As = NIL; do
        { ADV(Ap,&A1,&Ap);
        if (i > 1) A1 = PPERMV(r,A1,P); s = PUNT(r,A1);
        if (s == 2) goto Step4; else if (s == 1) goto Step3;
        As = COMP(A1,As); } while (!(Ap == NIL)); As = INV(As);
        if (!IPFZT1(r,As)) { t = 0; goto Step4; }

Step3: /* Check for completion. */ i = i + 1; if (i > r) goto Step4;
        P = PERMCY(P); goto Step2;

Step4: /* Return. */
                               /*Int*/ Ths = ACLOCK() - Ths;
                               /*Int*/ TMIPFZT[r] = TMIPFZT[r] + Ths;
        goto Return;

Return: /* Prepare for return. */
       return(t);
}
