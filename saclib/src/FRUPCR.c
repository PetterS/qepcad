/*==========================================================================
		      Ap <- FRUPCR(A,n)

Finite ring univariate polynomial convert representation.

Inputs
  n : a BETA-digit, n >= 1.
  A : in (Z/(m)[x])/(M)[y], where m is a BETA-digit and M has degree n.

Outputs
  Ap : in (Z/(m)[x])/(M)[y].  Ap = A, where Ap is in array representation.
==========================================================================*/
#include "saclib.h"

Word **FRUPCR(A,n)
       Word A,n;
{
       Word **Ap,*C,At,a,d,c,e,f,i,j;
       
Step1: /* A = 0. */
       if (A == 0)  {
	  Ap = FRAPFMD(0,n);
	  goto Return; }

Step2: /* Get array for Ap and initialize. */
       d = PDEG(A);
       Ap = FRAPGET(d,n);
       FRAPDEG(Ap) = d;
       for (i = 0; i <= d; i++) {
	  C = FRAPCF(Ap,i);
	  for (j = 0; j <= n; j++)
	     MAPCF(C,j) = 0;
	  MAPDEG(C) = 0; }

Step3: /* Copy the coefficients. */
       At = A;
       while (At != 0) {
	  PADV(At,&e,&c,&At);
	  C = FRAPCF(Ap,e);
	  MAPDEG(C) = PDEG(c);
	  while (c != 0) {
	     PADV(c,&f,&a,&c);
	     MAPCF(C,f) = a; } }

Return: /* Prepare for return. */
       return(Ap);
}
