/*===========================================================================
		      Ap <- MAPFMUPS(A,k)

Modular array polynomial from modular univariate polynomial,
specify array size.

Input
  A : a modular univariate polynomial.
  k : a BETA-digit, k >= PDEG(A).

Output
  Ap: the same polynomial converted to array representation where the array
      will be large enough to hold a polynomial of degree k.
===========================================================================*/
#include "saclib.h"

Word *MAPFMUPS(A,k)
       Word A,k;
{
       Word n,*Ap,As,i;

Step1: /* Get array. */  
       Ap = MAPGET(k);

Step2: /* A = 0. */
       if (A == 0) { 
	  MAPDEG(Ap) = 0;
	  MAPCF(Ap,0) = 0;
	  goto Return; }

Step3: /* A != 0. */
       n = PDEG(A); 
       MAPDEG(Ap) = n;
       As = A; 
       for (i = n; i >= 0; i--)
	  if (As == 0 || PDEG(As) != i)
	     MAPCF(Ap,i) = 0;
	  else {
	     MAPCF(Ap,i) = PLDCF(As);
	     As = PRED(As); }
       
Return: /* Prepare for return. */
       return(Ap);
}
