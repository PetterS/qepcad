/*===========================================================================
		       MAPTPR(m,n,A,B,C)

Modular array polynomial truncated product.

Inputs
  m : a BETA-digit.
  n   : in Z, n >= 0.
  A,B : in Z/(m)[x].  A and B are in array representation.
  C : an array large enough to hold a polynomial of degree n-1.

Side effects.
  C(x) = A(x)*B(x) (modulo x^n) is computed and put in C.
  C(x) = 0 or deg(C(x)) < n.
===========================================================================*/
#include "saclib.h"

void MAPTPR(m,n,A,B,C)
       Word m,n,*A,*B,*C;
{
       Word *Ct,*Cs,*Cp,*T,ap,bp,i,j,k,d,c,np;

Step1: /* n = 0 or A = 0 or B = 0. */
       if (n == 0 || MAPZERO(A) || MAPZERO(B)) {
	  MAPDEG(C) = 0;
	  MAPCF(C,0) = 0;
	  goto Return; }

Step2: /* General case. */
       ap = MAPDEG(A);
       bp = MAPDEG(B);
       Cp = MAPGET(n-1);
       Cs = MAPGET(n-1);
       Ct = MAPGET(n-1);
       MAPDEG(Cs) = 0;
       for (i = 0; i < n; i++)
	  MAPCF(Cs,i) = 0;
       np = MIN(n,bp+1);
       for (i = 0; i < np; i++) {
	  for (j = 0; j < i; j++)
	     MAPCF(Cp,j) = 0;
	  d = 0;
	  for (j = 0; j < n-i && j <= ap; j++) {
	     k = i+j;
	     c = MDPROD(m,MAPCF(A,j),MAPCF(B,i));
	     MAPCF(Cp,k) = c;
	     if (c != 0)
		d = k; }
	  MAPDEG(Cp) = d;
	  MAPSUM(m,Cs,Cp,Ct);
	  T = Cs;
	  Cs = Ct;
	  Ct = T; }
       MAPFREE(Ct);
       MAPFREE(Cp);
       MAPASSIGN(Cs,C);
       MAPFREE(Cs);

Return: /* Prepare for return. */
       return;
}
