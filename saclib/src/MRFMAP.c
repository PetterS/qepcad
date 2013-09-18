/*==========================================================================
			  MRFMAP(A,n,M,r)

Matrix row from modular array polynomial. 

Inputs
  A : a modular array polynomial.
  n : a positive BETA-digit, deg(A) < n.
  M : an n*n matrix.
  r : a BETA-digit, 0 <= r < n.

Side effect
  The coefficients of A are stored in the rth row of M, i.e.,
  MATELT(M,r,i) will be set to the coefficient of x^i in A.
===========================================================================*/
#include "saclib.h"

void MRFMAP(A,n,M,r)
       Word *A,n,**M,r;
{
       Word i,m;

Step1: /* Put coefficients in rth row. */
       m = MAPDEG(A);
       for (i = 0; i <= m; i++)
	  MATELT(M,r,i) = MAPCF(A,i);
       for (i = m + 1; i < n; i++)
	  MATELT(M,r,i) = 0;

Return: /* Prepare for return. */
       return;
}
