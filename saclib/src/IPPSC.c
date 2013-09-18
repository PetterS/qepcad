/*===========================================================================
			     P <- IPPSC(r,A,B)

Integral polynomial principal subresultant coefficients.

Inputs
   r : a BETA-digit, r > 0.
 A,B : in Z[x_1,...,x_r], A and B are of positive degree in the main
       variable.

Outputs
  P  : a list of the non-zero principal subresultant coefficients of
       A and B.  If i < j then psc_{i}(A,B) precedes psc_{j}(A,B) in P.
===========================================================================*/
#include "saclib.h"

Word IPPSC(r,A,B)
       Word r,A,B;
{
       Word G1,G2,G3,Gh3,P,d0,d1,g1,h0,h1,hs0,hs1,i,n1,n2,n3,rp,t;

Step1: /* Initialize. */
       n1 = PDEG(A);
       n2 = PDEG(B);
       if (n1 > n2) {
	  G1 = A;
	  G2 = B; }
       else {
	  G1 = B;
	  G2 = A;
	  t = n1;
	  n1 = n2;
	  n2 = t; }
       d0 = 0;
       d1 = n1 - n2;
       rp = r - 1;
       i = 1;
       P = NIL;

Step2: /* Compute Gh_{i+2}. */
       if (G2 == 0)
	  goto Step3;
       Gh3 = IPPSR(r,G1,G2);
       n3 = PDEG(Gh3);
       if (Gh3 == 0)
	  goto Step3;
       if (EVEN(d1) == 1)
	  Gh3 = IPNEG(r,Gh3);

Step3: /* Compute hi. */
       if (i > 1) {
	  g1 = PLDCF(G1);
	  h1 = IPEXP(rp,g1,d0);
	  if (i > 2) {
	     hs0 = IPEXP(rp,h0,d0 - 1);
	     h1 = IPEQ(rp,h1,hs0);
	     P = COMP(h1,P);
	     if (G2 == 0)
		goto Return; } }

Step4: /* Compute G_{i+2}. */
       if (i == 1 || Gh3 == 0)
	  G3 = Gh3;
       else {
	  hs1 = IPEXP(rp,h1,d1);
	  hs1 = IPPROD(rp,g1,hs1);
	  hs1 = PMON(hs1,0);
	  G3 = IPEQ(r,Gh3,hs1);
	  hs1 = 0; }

Step5: /* Update. */
       n1 = n2;
       n2 = n3;
       d0 = d1;
       d1 = n1 - n2;
       G1 = G2;
       G2 = G3;
       if (i > 1)
	  h0 = h1;
       i = i + 1;
       goto Step2;

Return: /* Prepare for return. */
       return(P);
}
