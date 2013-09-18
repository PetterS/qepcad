/*===========================================================================
                              C <- IPEQ(r,A,B)

Integral polynomial exact quotient.

Inputs
   r   : a beta-digit, r >= 0, the number of variables.
   A,B : in Z[x_1,...,x_r], B a non-zero divisor of A.

Output
   C   : in Z[x_1,...,x_r], C = A / B.
===========================================================================*/
#include "saclib.h"

Word IPEQ(r,A,B)
       Word r,A,B;
{
       Word a,Ah,Ap,b,bh,bp,Bb,Bp,Bh,c,C,e,f,g,h,k,m,n,rp;

Step1: /* A = 0. */
       if (A == 0) {
	  C = 0;
	  goto Return; }

Step2: /* r = 0. */
       if (r == 0) {
	  C = IEQ(A,B);
	  goto Return; }

Step3: /* Set m = deg(A), n = deg(B), k = deg(C). */
       m = PDEG(A);
       n = PDEG(B);
       k = m - n;

Step4: /* Set b = ldcf(B), B_ = red(B), r' = r - 1. */
       b = PLDCF(B);
       Bb = PRED(B);
       rp = r - 1;

Step5: /* Set A^ to A(x) with terms of degree less than n deleted. */
       Ap = A;
       Ah = NIL;
       while (Ap != NIL && PDEG(Ap) >= n) {
	  ADV2(Ap,&e,&a,&Ap);
	  Ah = COMP2(a,e,Ah); }
       Ah = INV(Ah);
       C = NIL;

Step6: /* Compute next term, c x^g, of C. */
       PADV(Ah,&e,&a,&Ah);
       if (rp == 0)
	  c = IEQ(a,b);
       else
	  c = IPEQ(rp,a,b);
       g = e - n;
       C = COMP2(c,g,C);

Step7: /* B_ = 0? */
       if (Bb == 0)
	  if (Ah == 0)
	     goto Step10;
	  else
	     goto Step6;

Step8: /* Compute B^ = c x^g B_ minus terms of degree less than n. */
       Bp = Bb;
       Bh = NIL;
       h = n - g;
       while (Bp != NIL && FIRST(Bp) >= h) {
	  ADV2(Bp,&f,&bp,&Bp);
	  bh = IPPROD(rp,bp,c);
	  Bh = COMP2(bh,f + g,Bh); }
       Bh = INV(Bh);
       if (Bh == NIL)
	  Bh = 0;

Step9: /* Set A^ = A^ - B^ and, if A^ /= 0, go back to Step5. */
       Ah = IPDIF(r,Ah,Bh);
       if (Ah != 0)
	  goto Step6;
        
Step10: /* Invert list for C */
       C = INV(C);

Return: /* Prepare for return. */
        return(C);
}
