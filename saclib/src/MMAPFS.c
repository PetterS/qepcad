/*===========================================================================
		      L <- MMAPFS(p,A,B,d)

Medium modulus array polynomial factorization, special.

Inputs
  p : a medium prime.
  A : in Z/(p)[x], deg(A) >= 2, monic and squarefree.
      A is in array representation.
  B : a list (B_1,...,B_r) of monic elements of Z/(p)[x] in array
      representation.  The B_i's constitute a basis for the space of all
      polynomials C of degree less than deg(Ap) such that Ap is a divisor
      of C^p - C.  Furthermore, B_1 = 1.
  d : a BETA-digit, d > 0, such that Ap has no irreducible factor of
      degree less than d.

Outputs
  L : a list consisting of all the monic irreducible factors of Ap of
      positive degree in array representation.
===========================================================================*/
#include "saclib.h"

Word MMAPFS(p,A,B,d)
       Word p,*A,B,d;
{
       Word *Ap,*A1,*B1,Bp,*C,*Q,*T,L,Lp,e,f,i,k,r,s;
       
Step1: /* A irreducible. */
       Ap = MAPCOPY(A);
       L = NIL;
       L = PTRCOMP(Ap,L);
       r = PTRLENGTH(B);
       if (r == 1)
	  goto Return;

Step2: /* Factorize. */
       Bp = PTRRED(B);
       k = 1;
       do {
	  Lp = NIL;
	  PTRADV(Bp,&B1,&Bp);
	  do {
	     PTRADV(L,&A1,&L);
	     e = MAPDEG(A1);
	     if (e > d) {
		s = 0;
		i = 0;
		do {
		   C = MMAPGCD(p,A1,B1);
		   f = MAPDEG(C);
		   if (f == 0)
		      MAPFREE(C);
		   else {
		      if (f == e) {
			 s = 1;
			 MAPFREE(C); }
		      else {
			 Lp = PTRCOMP(C,Lp);
			 Q = MAPGET(MAPDEG(A1)-MAPDEG(C));
			 MMAPQR(p,A1,C,Q);
			 T = A1;
			 A1 = Q;
			 MAPFREE(T);
			 k++;
			 if (k == r) {
			    Lp = PTRCOMP(A1,Lp);
			    L = CONC(Lp,L);
			    goto Return; }
			 e = MAPDEG(A1);
			 if (e == d)
			    s = 1; } }
		   MAPCF(B1,0) = (MAPCF(B1,0) + 1) % p;
		   i++;	}
		while (i != p && s != 1); }
	     Lp = PTRCOMP(A1,Lp); }
	  while (L != NIL);
	  L = Lp; }
       while (1);

Return: /* Prepare for return. */
       return(L);
}
