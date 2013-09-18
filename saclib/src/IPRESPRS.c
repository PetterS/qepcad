/*===========================================================================
			     R <- IPRESPRS(r,A,B)

Integral polynomial resultant, polynomial remainder sequence method.

Inputs
   r : a BETA-digit, r > 0.
   A, B :  integral polynomials having positive degrees.

Output
   R : the resultant of A and B.
===========================================================================*/
#include "saclib.h"

Word IPRESPRS(r,A,B)
	BDigit r;
	Word A,B;
{
	Word G1,G2,G3,Gh3,R,g1,g2,gs1,gs2,h0,h1,h2,hs0,hs1;
	BDigit d0,d1,i,m,n,n1,n2,n3,rp,s;

Step1: /* Initialize. */
	m = PDEG(A);
	n = PDEG(B);
	s = 1;
	if (m >= n) {
           G1 = A;
           G2 = B;
	   n1 = m;
	   n2 = n; }
	else {
	   G1 = B;
	   G2 = A;
	   n1 = n;
	   n2 = m;
	   if (ODD(m) && ODD(n))
	      s = -1; }
        d0 = 0;
        d1 = n1 - n2;
        rp = r - 1;
        i = 1;

Step2: /* Compute Gh_{i+2} and n_{i+2}. */
       Gh3 = IPPSR(r,G1,G2);
       if (Gh3 == 0) {
	  R = 0;
	  goto Return; }
       if (EVEN(d1))
	  Gh3 = IPNEG(r,Gh3);
       n3 = PDEG(Gh3);

Step3: /* Compute h_i. */
       if (i > 1) {
	  g1 = PLDCF(G1);
	  h1 = IPEXP(rp,g1,d0);
	  if (i > 2) {
	     hs0 = IPEXP(rp,h0,d0 - 1);
	     h1 = IPEQ(rp,h1,hs0); } }

Step4: /* Compute G_{i+2}. */
       if (i == 1)
	  G3 = Gh3;
       else {
	  hs1 = IPEXP(rp,h1,d1);
	  hs1 = IPPROD(rp,g1,hs1);
	  hs1 = PMON(hs1,0);
	  G3 = IPEQ(r,Gh3,hs1); }

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
	if (n2 > 0)
           goto Step2;

Step6: /* Finish. */
	g1 = PLDCF(G1);
	g2 = PLDCF(G2);
	if (d1 == 1)
	   R = g2;
	else {
	   if (i == 2) {
	      R = IPEXP(rp,g2,d1);
	      if (d0 != 1) {
	         gs1 = IPEXP(rp,g1,d0 * d1 - d0);
	         R = IPEQ(rp,R,gs1); } }
	   else {
	      if (d0 == 1)
	         h1 = g1;
	      else {
	         hs0 = IPEXP(rp,h0,d0-1);
	         gs1 = IPEXP(rp,g1,d0);
	         h1 = IPEQ(rp,gs1,hs0); }
	      hs1 = IPEXP(rp,h1,d1-1);
	      gs2 = IPEXP(rp,g2,d1);
	      h2 = IPEQ(rp,gs2,hs1);
	      R = IPPROD(rp,g2,h2);
	      R = IPEQ(rp,R,g2); } }
	if (s < 0)
	   R = IPNEG(rp,R);

Return: /* Return R. */
       return(R);
}
