/*===========================================================================
		       L <- MMPFBL(p,A,d)

Medium modulus polynomial factorization, Berlekamp algorithm.

Inputs
  p : a medium prime.
  A : in Z/(p), deg(A) = n >= 2, monic and squarefree.
      A is in list representation.
  d : a BETA-digit, d > 0, such that A has no irreducible factor of
      degree less than d.

Outputs
  L : a list of all the distinct monic irreducible factors of A of
      positive degree in list representation.
===========================================================================*/
#include "saclib.h"

Word MMPFBL(p,A,d)
       Word p,A,d;
{
       Word *Ap,B,*B1,L,Lp,*L1,**Q,i,n,N,*N1;

Step1: /* Construct the matrix Q-I. */
       Ap = MAPFMUP(A);
       Q = MMAPBM(p,Ap);
       n = MAPDEG(Ap);
       for (i = 0; i < n; i++) 
	  MATELT(Q,i,i) = MDDIF(p,MATELT(Q,i,i),1);

Step2: /* Generate null space basis and convert to polynomials. */
       N = MMAMNSB(p,n,Q);
       B = NIL;
       do {
	  PTRADV(N,&N1,&N);
	  B1 = MAPFV(n,N1);
	  FREEARRAY(N1);
	  B = PTRCOMP(B1,B); }
       while (N != NIL);

Step3: /* Factorize. */
       Lp = MMAPFS(p,Ap,B,d);
       
Step4: /* Convert to lists. */
       L = NIL;
       do {
	  PTRADV(Lp,&L1,&Lp);
	  L = COMP(MUPFMAP(L1),L);
	  MAPFREE(L1); }
       while (Lp != NIL);

Step5: /* Free arrays. */
       MAPFREE(Ap);
       FREEMATRIX(Q,n);
       do {
	  PTRADV(B,&B1,&B);
	  MAPFREE(B1); }
       while(B != NIL);

Return: /* Prepare for return. */
       return(L);
}
