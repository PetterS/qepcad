/*===========================================================================
			     L <- IPRCHS(A,I,k)

Integral polynomial real root calculation, high-precision special.

Inputs
  A : in Z[x], positive, primitive, squarefree, deg(A) > 0, gcd(A,A'')=1.
  I : either the null list () or a standard interval or an interval
      whose positive and non-positive parts are standard.
  k : a BETA-digit.

Outputs
  L : a list (I_1,...,I_r) of binary rational isolating intervals
      I_j=(a_j,b_j) for the r distinct real roots of A if I=(), for the
      r distinct real roots of A in I if I /= (), with b_j - a_j <= 2^k.
      I_j is a left-open and right-closed interval if a_j /= b_j,
      a one-point interval if a_j=b_j.
===========================================================================*/
#include "saclib.h"

Word IPRCHS(A,I,k)
       Word A,I,k;
{
       Word J,L,L1,b,s,sp,spp,t;

Step1: /* Find strong isolation list for A. */
       L = NIL;
       L1 = IPSRM(A,I);
       if (L1 == NIL)
	  goto Return;

Step2: /* Refine isolation list. */
       do {
	  ADV(L1,&J,&L1);
	  b = SECOND(J);
	  if (IUPBRE(A,b) == 0)
	     J = LIST2(b,b);
	  else {
	     IPRCNP(A,J,&sp,&spp,&J);
	     t = RILC(J,k);
	     if (t == 0) {
		s = sp * spp;
		J = IPRCN1(A,J,s,k); } }
	  L = COMP(J,L); }
       while (L1 != NIL);
       L = INV(L);

Return: /* Prepare for return. */
       return(L);
}
