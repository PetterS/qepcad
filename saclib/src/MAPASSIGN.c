/*===========================================================================
			 MAPASSIGN(A,B)

Modular array polynomial assignment.

Inputs
  A : a modular array polynomial.
  B : an array at least as large as deg(A)+2.

Side effects
  B is modified so that it contains the polynomial A.
===========================================================================*/
#include "saclib.h"

void MAPASSIGN(A,B)
       Word *A,*B;
{
       Word i,n;

Step1: /* Modify B. */
       n = MAPDEG(A);
       MAPDEG(B) = n;
       for (i = 0; i <= n; i++)
	  MAPCF(B,i) = MAPCF(A,i);

Return: /* Prepare for return. */
       return;
}
