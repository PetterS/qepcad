/*====================================================================
		       L <- IPRRIRSB(A,k)

Integral polynomial real root isolation and refinement,
Sturm, bisection.

Inputs
   A: in Z[x], squarefree.
   k: a BETA-integer.

Output
   L: a list (I_1,...,I_r) of open and one-point logarithmic
      standard isolating intervals for the real roots of A
      having widths of 2^{k} or less, I_1 < I-2 < ... < I_r.
=====================================================================*/
#include "saclib.h"

Word IPRRIRSB(A,k)
       Word A,k;
{
       Word I,J,L,M,n,t,u;

Step1: /* Compute a list, M, of isolating intervals. */
       M = IPRRIS(A);

Step2: /* Compute the trend, t, of the first interval. */
       n = PDEG(A);
       t = ISIGNF(PLDCF(A));
       if (EVEN(n) == 1)
	  t = -t;

Step3: /* Compute a list, L, of refined intervals. */
       L = NIL;
       u = t;
       while (M != NIL) {
	  ADV(M,&I,&M);
	  J = IPIIRB(A,I,u,k);
	  L = COMP(J,L);
	  u = - u; }
       L = INV(L);

Return: /* Return L. */
       return(L);
}
