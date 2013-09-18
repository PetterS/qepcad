/*===========================================================================
			Ap <- MUPFMAP(A)

Modular univariate polynomial from modular array polynomial.

Input
  A : a modular polynomial in array representation.

Output
  Ap: the same polynomial converted to list representation.
===========================================================================*/
#include "saclib.h"

Word MUPFMAP(A)
       Word *A;
{
       Word Ap,a,i,n;

Step1: /* A = 0. */
       if (MAPZERO(A)) {
	  Ap = 0;
	  goto Return; }

Step2: /* A != 0. */
       Ap = NIL;
       n = MAPDEG(A);
       for (i = 0; i <= n; i++) {
	  a = MAPCF(A,i);
	  if (a != 0)
	     Ap = PPLT(i,a,Ap); }
       
Return: /* Prepare for return. */
       return(Ap);
}
