/*===========================================================================
			Ap <- MAPCOPY(A)

Modular array polynomial copy.

Input
  A : a modular array polynomial.

Output
  Ap: an array of size MAPDEG(A)+2 containing a copy of the polynomial A.
===========================================================================*/
#include "saclib.h"

Word *MAPCOPY(A)
       Word *A;
{
       Word *Ap,n,i;

Step1: /* Get array. */
       n = MAPDEG(A);
       Ap = MAPGET(n);

Step2: /* Copy. */
       MAPDEG(Ap) = n;
       for (i = 0; i <= n; i++)
	  MAPCF(Ap,i) = MAPCF(A,i);

Return: /* Prepare for return. */
       return(Ap);
}
