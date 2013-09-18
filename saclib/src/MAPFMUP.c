/*===========================================================================
			Ap <- MAPFMUP(A)

Modular array polynomial from modular univariate polynomial.

Input
  A : a modular univariate polynomial.

Output
  Ap: the same polynomial converted to array representation.
===========================================================================*/
#include "saclib.h"

Word *MAPFMUP(A)
       Word A;
{
       Word n,*Ap,As,i;

Step1: /* Get array. */  
       n = PDEG(A); 
       Ap = MAPGET(n);

Step2: /* A = 0. */
       if (A == 0) { 
	  MAPDEG(Ap) = 0;
	  MAPCF(Ap,0) = 0;
	  goto Return; }

Step3: /* A != 0. */
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
