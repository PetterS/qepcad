/*===========================================================================
			     L <- IPRCH(A,I,k)

Integral polynomial real root calculation, high precision.

Inputs
  A : in Z[x], deg(A) > 0.
  I : either the null list () or a standard interval or an interval
      whose positive and non-positive parts are standard.
  k : a BETA-digit.

Outputs
  L : a list ((e_1,I_1),...,(e_r,I_r)) where the e_j are BETA-digits,
      1 <= e_1 <= ... <= e_r, 
      and the I_j are binary rational isolating intervals, I_j=(a_j,b_j), 
      for the r distinct real roots of A if I = (), or 
      for the r distinct real roots of A in I if I /= ().
      ej is the multiplicity of the root alpha_j in I_j and |b_j-a_j| <= 2^k.
      I_j is a left-open and right-closed interval if a_j < b_j, 
      a one-point interval if a_j=b_j.
===========================================================================*/
#include "saclib.h"

Word IPRCH(A,I,k)
       Word A,I,k;
{
       Word A1,Ab,J,L,L1,L2,P,e;

Step1: /* Squarefree factorization. */
       Ab = IPABS(1,A);
       L1 = IPSFSD(1,Ab);

Step2: /* Compute roots of factors. */
       L = NIL;
       do {
	  ADV(L1,&P,&L1);
	  FIRST2(P,&e,&A1);
	  L2 = IPRCHS(A1,I,k);
	  while (L2 != NIL) {
	     ADV(L2,&J,&L2);
	     P = LIST2(e,J);
	     L = COMP(P,L); } }
       while (L1 != NIL);
       L = INV(L);

Return: /* Prepare for return. */
       return(L);
}
