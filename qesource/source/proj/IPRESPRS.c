/*===========================================================================
                      R <- IPRESPRS(r,A,B)

Integral polynomial resultant, subresultant polynomial remainder 
sequence algorithm. 

Inputs
   r : a BETA-digit, r > 0.
 A,B : in Z[X1,...,Xr], A and B non-zero, deg(A) >= deg(B).

Outputs
  R : the resultant of A and B, computed using the 
      (non-modular) subresultant prs algorithm.
===========================================================================*/
#ifdef _OLD_

Word IPRESPRS(Word r, Word A, Word B)
{
       Word G1,G2,G3,Gh3,R,S,d0,d1,g1,h0,h1,hs0,hs1,i,n1,n2,n3,rp,a,b;

Step1: /* Initialize. */
       a = PDEG(A);
       b = PDEG(B);
       if (a < b) {
	 G1 = B;
	 G2 = A; }
       else {
	 G1 = A;
	 G2 = B; }
		      if (b == 0) {
	              R = 1;                                 /* Added 2/97 */
	              for(i = 1; i < r; i++) R = LIST2(0,R); /* Added 2/97 */
		      goto Return; }                         /* Added 2/97 */
       n1 = PDEG(G1);
       n2 = PDEG(G2);
       d0 = 0;
       d1 = n1 - n2;
       rp = r - 1;
       i = 1;

Step2: /* Compute Gh_{i+2}. */
       Gh3 = IPPSR(r,G1,G2);
       if (Gh3 == 0) {
	 if (PDEG(S) > 0)
	   R = 0;
	 else {
	   R = PLDCF(S);
	   if (a < b) {
	     if (ODD(a) && ODD(b))
	       R = IPNEG(rp,R); } }
         goto Return; }
       if (EVEN(d1) == 1)
         Gh3 = IPNEG(r,Gh3);
       n3 = PDEG(Gh3);

Step3: /* Compute hi. */
       if (i > 1) {
         g1 = PLDCF(G1);
         h1 = IPEXP(rp,g1,d0);
         if (i > 2) {
           hs0 = IPEXP(rp,h0,d0 - 1);
           h1 = IPQ(rp,h1,hs0);
           hs0 = 0; } }

Step4: /* Compute G_{i+2}. */
       if (i == 1)
         G3 = Gh3;
       else {
         hs1 = IPEXP(rp,h1,d1);
         hs1 = IPPROD(rp,g1,hs1);
         hs1 = LIST2(0,hs1);
         G3 = IPQ(r,Gh3,hs1);
         hs1 = 0;
         Gh3 = 0; }

Step5: /* Update. */
       S = G3;
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
       return(R);
}

#else

/*===========================================================================
			     R <- IPRESPRS(r,A,B)

Integral polynomial resultant, polynomial remainder sequence method.

Inputs
   r : a BETA-digit, r > 0.
   A, B :  integral polynomials having positive degrees.

Output
   R : the resultant of A and B.
===========================================================================*/

Word IPRESPRS(r,A,B)
	BDigit r;
	Word A,B;
{
	Word G1,G2,G3,Gh3,R,g1,g2,gs1,gs2,h0,h1,h2,hs0,hs1;
	BDigit d0,d1,i,n1,n2,n3,rp;

Step1: /* Initialize. */
	if (PDEG(A) >= PDEG(B)) {
           G1 = A;
           G2 = B; }
	else {
	   G1 = B;
	   G2 = A; }
        n1 = PDEG(G1);
        n2 = PDEG(G2);
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

Return: /* Return R. */
       return(R);
}
#endif
