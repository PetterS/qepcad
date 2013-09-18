/*=====================================================================
			L <- IBPPOS(A,a,b,e,k)

Integral bivariate polynomial points on sections.

Inputs
   A:    an integral bivariate polynomial A(x,y) of positive
         degree in y.
   a,b:  rational numbers, a < b, such that A(x,y) is
         delineable on the open interval (a,b).
   e:    a positive binary rational number.
   k:    an integer.

Output
   L:  Let r be the number of real roots of A(c,y) for any
       c in (a,b).  If r = 0 then L = ().  Otherwise, let m
       be the least integer such that m*e > a, n the greatest
       integer such that n*e < b.  Let a_1,a_2,...,a_h be the
       numbers m*e,(m+1)*e,...,n*e.  L is a list (a_1,L_1,
       ,a_2,L_2,...,a_h,L_h), where each a_i is a logarithmic
       binary rational number  and L_i is a list (b_1,b_2,...,b_r)
       of logarithmic binary rational numbers such that the i-th
       real root of A(a_i,y) is either equal to b_i or is in
       the open interval (b_i,b_i + 2^{-k}) for 1 <= i <= r.
======================================================================*/
#include "saclib.h"

Word IBPPOS(A,a,b,e,k)
	Word A,a,b,e,k;
{
	Word a1,a2,a3,B,c,d,E,I,L,L1,L2,m,q;

Step1: /* Compute m and initialize c to a_1. */
	q = RNQ(a,e);
	m = ISUM(RNFLOR(q),1);
	c = RNPROD(RNINT(m),e);

Step2: /* Initialize L. */
	L = NIL;

Step3: /* Test for completion. */
	if (RNCOMP(c,b) >= 0)
	   goto Step9;

Step4: /* Compute B(y) = A(c,y). */
	B = IPBREI(2,A,1,c);

Step5: /* If this is the first or second loop execution, isolate and
refine the real roots of B, extract the left endpoints, and go to
Step7, but if r = 0, return. */

        if (L == NIL || RED2(L) == NIL) {
           L1 = IPRRIRDB(B,-k);
           if (L1 == NIL)
              goto Return;
           L2 = NIL;
           while (L1 != NIL) {
              ADV(L1,&I,&L1);
              d = FIRST(I);
              L2 = COMP(d,L2); }
           L1 = INV(L2);
           goto Step7; }

Step6: /*  Otherwise, compute estimates for the roots using linear
interpolation and apply IUPRRAFE. */

	L2 = FIRST(L);
	L1 = THIRD(L);
	E = NIL;
	while (L2 != NIL) {
	   ADV(L1,&a1,&L1);
	   ADV(L2,&a2,&L2);
	   d = LBRNDIF(a2,a1);
	   a3 = LBRNSUM(a2,d);
	   E = COMP(a3,E); }
	E = INV(E);
	L1= IUPRRAFE(B,E,k);

Step7: /* Prefix c and L1 to the list L. */
	L = COMP2(L1,RNLBRN(c),L);

Step8: /* Increment c and go back to Step3. */
	c = RNSUM(c,e);
	goto Step3;

Step9: /* Invert the list L. */
	L = INV(L);

Return: /* Return L. */
	return(L);
}
