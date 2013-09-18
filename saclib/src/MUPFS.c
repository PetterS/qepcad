/*===========================================================================
			    L <- MUPFS(p,A,B,d)

Modular univariate polynomial factorization, special.

Inputs
  p : a BETA-digit, p prime.
  A : in Z/(p)[X], deg(A) >= 2, A monic, squarefree.
  B : a list (B1,...,Br), with Bi in Z/(p)[X], Bi monic. The Bi
      constitute a basis for the space of all polynomials c of
      degree less than deg(A) such that A is a divisor of c^p - c.
      Furthermore, B(1) = 1.
  d : a BETA-digit, d > 0, such that A has no irreducible factor of
      degree less than d.

Outputs
  L : a list consisting of all the monic irreducible factors of A of
      positive degree.
===========================================================================*/
#include "saclib.h"

Word MUPFS(p,A,B,d)
       Word p,A,B,d;
{
       Word A1,B1,Bp,C,L,Lp,c,e,f,i,k,r,s;

Step1: /* A irreducible. */
       L = LIST1(A);
       r = LENGTH(B);
       if (r == 1)
	  goto Return;

Step2: /* Factorize. */
       Bp = RED(B);
       k = 1;
       c = LIST2(0,1);
       do {
	  Lp = NIL;
	  ADV(Bp,&B1,&Bp);
	  do {
	     ADV(L,&A1,&L);
	     e = FIRST(A1);
	     if (e > d) {
		s = 0;
		i = 0;
		do {
		   C = MUPGCD(p,A1,B1);
		   f = FIRST(C);
		   if (f > 0) {
		      if (f == e)
			 s = 1;
		      else {
			 Lp = COMP(C,Lp);
			 A1 = MPQ(1,p,A1,C);
			 k = k + 1;
			 if (k == r) {
			    Lp = COMP(A1,Lp);
			    L = CONC(Lp,L);
			    goto Return; }
			 e = FIRST(A1);
			 if (e == d)
			    s = 1; } }
		   B1 = MPSUM(1,p,c,B1);
		   i = i + 1; }
		while (i != p && s != 1); }
	     Lp = COMP(A1,Lp); }
	  while (L != NIL);
	  L = Lp; }
       while (1);

Return: /* Prepare for return. */
       return(L);
}
