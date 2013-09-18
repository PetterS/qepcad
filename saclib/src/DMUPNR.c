/*===========================================================================
			     C <- DMUPNR(p,A,B)

Dense modular univariate polynomial natural remainder.

Inputs
  A, B : in Z/(p)[X] dense representation,
         A,B different from 0, deg(A) >= deg(B).
  p  : a prime BETA-digit.
  
Outputs
  C  : in Z/(p)[X], the natural remainder of B.  

Side effects
  The list for A is modified.
===========================================================================*/
#include "saclib.h"

Word DMUPNR(p,A,B)
       Word p,A,B;
{
       Word Ap,App,As,Bp,Bpp,Bs,C,a,b,bp,c,k,m,n;

Step1: /* Deg(B)=0. */
       n = FIRST(B);
       if (n == 0) {
	  C = 0;
	  goto Return; }

Step2: /* Deg(B) positive. */
       Bp = RED(B);
       ADV(Bp,&b,&Bs);
       bp = MDINV(p,b);
       As = A;
       do {
	  ADV(As,&k,&Ap);
	  m = -1;
	  ADV(Ap,&a,&App);
	  c = MDPROD(p,a,bp);
	  Bpp = Bs;
	  do {
	     ADV(Bpp,&b,&Bpp);
	     b = MDPROD(p,b,c);
	     a = FIRST(App);
	     a = MDDIF(p,a,b);
	     k = k - 1;
	     if (m < 0 && a != 0) {
		m = k;
		As = Ap; }
	     SFIRST(App,a);
	     Ap = App;
	     App = RED(Ap); }
	  while (Bpp != NIL);
	  while (m < 0 && App != NIL) {
	     k = k - 1;
	     if (FIRST(App) != 0) {
		m = k;
		As = Ap; }
	     Ap = App;
	     App = RED(Ap); }
	  if (m >= 0)
	     SFIRST(As,m); }
       while (m >= n);
       if (m >= 0)
	  C = As;
       else
	  C = 0;

Return: /* Prepare for return. */
       return(C);
}
