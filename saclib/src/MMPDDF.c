/*===========================================================================
			L <- MMPDDF(p,A)

Medium modulus polynomial distinct-degree factorization.

Inputs
  p : a medium prime.
  A : in Z/(p)[X], deg(A) >= 2, monic and squarefree.
      A is in list representation.

Outputs
  L : a list ((n_1,A_1),...,(n_k,A_k)), with n_i in Z, n_i > 0,
      n_1 < ... < n_k, and each A_i is in Z/(p)[x], in list
      representation, and is the product of all irreducible
      monic factors of A of degree n_i.
===========================================================================*/
#include "saclib.h"

Word MMPDDF(p,Ap)
       Word p,Ap;
{
       Word *A,**Q,n,*B,*Bp,*W,i,j,*C,*Cp,*D,L,Lp,L1,A1,b,d,e,k,w1;

Step1: /* Initialize. */
       A = MAPFMUP(Ap);
       Q = MMAPBM(p,A);
       n = MAPDEG(A)-1;
       B = MAPGET(n);
       Bp = GETARRAY(n+1);
       W = MAPGET(n);
       for (i = 0; i <= n; i++) 
	  MAPCF(B,i) = MATELT(Q,1,i);
       d = n;
       while (MAPCF(B,d) == 0)
	  d--;
       MAPDEG(B) = d;
       C = MAPCOPY(A);
       L = NIL;
       k = 1;

Step2: /* Compute A_k. */
       do {
	  MAPASSIGN(B,W);
	  w1 = MDDIF(p,MAPCF(W,1),1);
	  if (w1 == 0 && MAPDEG(W) == 1)
	     MAPDEG(W) = 0;
	  else
	     MAPCF(W,1) = w1;
	  D = MMAPGCD(p,W,C);
	  if (MAPDEG(D) > 0) {
	    L1 = COMP(k,PTRLIST1(D));
	     L = COMP(L1,L);
	     Cp = MAPGET(MAPDEG(C)-MAPDEG(D));
	     MMAPQR(p,C,D,Cp);
	     MAPFREE(C);
	     C = Cp; }
	  else 
	     MAPFREE(D);
	  k++;
	  e = MAPDEG(C);
	  if (e >= 2 * k) {
	     for (i = 0; i <= n; i++) {
		Bp[i] = MAPCF(B,i);
		MAPCF(B,i) = 0; }
	     for (i = 0; i <= n; i++) 
		for (j = 0; j <= n; j++) {
		   b =  (MAPCF(B,i) + Bp[j] * MATELT(Q,j,i)) % p;
		   MAPCF(B,i) = b; }
	     d = n;
	     while (MAPCF(B,d) == 0 && d > 0)
		d--;
	     MAPDEG(B) = d; }
	  else {
	     if (e > 0) {
	       L1 = COMP(e,PTRLIST1(C));
		L = COMP(L1,L); }
	     else
		MAPFREE(C);
	     L = INV(L);
	     goto Step3; } }
       while(1);

Step3: /* Convert to lists. */
       Lp = NIL;
       do {
	  ADV(L,&L1,&L);
	  ADV(L1,&e,&L1);
	  PTRADV(L1,&C,&L1);
	  A1 = MUPFMAP(C);
	  MAPFREE(C);
	  Lp = COMP(LIST2(e,A1),Lp); }
       while (L != NIL);
       L = INV(Lp);

Step4: /* Free arrays. */
       MAPFREE(A);
       MAPFREE(B);
       FREEARRAY(Bp);
       MAPFREE(W);
       FREEMATRIX(Q,n+1);

Return: /* Prepare for return. */
       return(L);
}
