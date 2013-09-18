/*=======================================================================
				A <- MPFFGEN(p,F)

Medium prime finite field generator.

Inputs
   p : a medium prime.
   F: a monic irreducible polynomial over Z_p in aray
      representation of degree n, n >= 2 and p^n < beta.

Output
   A: a monic primitive element of Z_p/(F) of minimum degree in
      array representation.
========================================================================*/
#include "saclib.h"

BDigit *MPFFGEN(p,F)
	BDigit p,*F;
{
	BDigit *A,*B,d,e,i,k,n,q,qp,t,u;
	Word L,Lp,M;

Step1: /* Let q' = q^n - 1.  Make a list L of all q'/d such that d is
          a prime divisor of q'. */
	n = MAPDEG(F);
	q = IEXP(p,n);
	qp = q - 1;
	L = IFACT(qp);
	M = LFML(L);
	L = NIL;
	do {
	   ADV(M,&d,&M);
	   L = COMP(qp/d,L); }
	while (M != NIL);

Step2: /* Search for a primitive element. */
	for (k = 1; k < n; k++) {
	   A = MAPGET(k);
	   MAPDEG(A) = k;
	   MAPCF(A,k) = 1;
	   for (i = 0; i < k; i++)
	      MAPCF(A,i) = 0;
	   do {
	      Lp = L;
	      do {
	         ADV(Lp,&e,&Lp);
	         B = MPFFEXP(p,F,A,e);
	         u = 0;
	         if (MAPDEG(B) == 0 && MAPCF(B,0) == 1)
	            u = 1;
	         MAPFREE(B); }
	      while (Lp != NIL && u == 0);
	      if (Lp == NIL && u == 0)
	         goto Return;
	      t = LEXNEXT(k,p-1,A); }
	   while (t == 1);
	   MAPFREE(A); }

Return: /* Return A. */
	return(A);
}
