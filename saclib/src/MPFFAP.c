/*=======================================================================
                         A <- MPFFAP(p,F,G)

Medium prime finite field array of powers.

Inputs
   p : a medium prime.
   F : an irreducible monic polynomial over Z_p in array representation
       defining a finite field GF(p^n), p^n < beta.
   G : a generator for GF(p^n) in array representation.

Output
   A : Let n = deg(F). A is an array of q = p^n beta-integers.
       A[0] = 0 and for 0 < i < q, A[i] = G^i(p).  G^i is
       evaluated in Z, not in Z_p.
=======================================================================*/
#include "saclib.h"

BDigit *MPFFAP(p,F,G)
	BDigit p,*F,*G;
{
	BDigit *A,*H,*K,i,n,q;

Step1: /* Compute q and get array. */
	n = MAPDEG(F);
	q = IEXP(p,n);
	A = GETARRAY(q);

Step2: /* Compute array elements. */
	A[0] = 0;
	H = MAPCOPY(G);
	A[1] = MAPSEV(H,p);
	for (i = 2; i < q; i++) {
	   K = MPFFPROD(p,F,H,G);
	   MAPFREE(H);
	   H = K;
	   A[i] = MAPSEV(H,p); }
	MAPFREE(H);

Return: /* Return A. */
	return(A);
}
