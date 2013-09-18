/*===========================================================================
			  L <- IPIISS(M,a,b,v1,v2)

Integral polynomial isolating interval search using a Sturm sequence.

Inputs  
  M : a list (A_1,A_2,...,A_t) of integral univariate polynomials.
      M is a Sturm sequence for A_1.
  a, b : binary rational numbers.  
  v1,v2 : integers.  v1 = var(M,a).  v2 = var(M,b)

Outputs
  L : a list (I_1,...,I_r) of isolating intervals for the real roots
      of A1 in the interval (a,b].  I_1 < I_2 < ... < I_r.
      Each I_j is a left-open right-closed binary rational interval.
===========================================================================*/
#include "saclib.h"

Word IPIISS(M,a,b,v1,v2)
       Word M,a,b,v1,v2;
{
       Word L,L1,L2,m,v;

Step1: /* Base case. */
       if (v1 - v2 == 0) {
	  L = NIL;
	  goto Return; }
       else
	  if (v1 - v2 == 1) {
	     L = LIST1(LIST2(a,b));
	     goto Return; }

Step2: /* Evaluate Sturm Sequence at midpoint. */
       m = RNPROD(RNSUM(a,b),LIST2(1,2));
       v = VAR(IPLEV(M,m));

Step3: /* Check left subinterval (a,m]. */
       L1 = IPIISS(M,a,m,v1,v);

Step4: /* Check right subinterval (m,b]. */
       L2 = IPIISS(M,m,b,v,v2);

Step5: /* Combine. */
       L = CONC(L1,L2);

Return: /* Prepare for return. */
       return(L);
}
