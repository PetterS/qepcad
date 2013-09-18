/*===========================================================================
			B = MAPMON(p,A)

Modular array polynomial monic.

Input
   A : a modular array polynomial.

Output
   B : the monic associate of A.
========================================================================*/
#include "saclib.h"

Word *MAPMON(p,A)
	BDigit p,*A;
{
	BDigit ap,b,*B,i,n;

Step1: /* Get array for B. */
        n = MAPDEG(A);
        B = MAPGET(n);

Step2: /* Compute the inverse of the leading coefficient. */
	ap = MDINV(p,MAPLDCF(A));
	b = MDPROD(p,ap,A[0]);

Step3: /* Store the degree and leading coefficients of B. */
	B[-1] = n;
	B[n] = 1;

Step4: /* Compute the coefficients of B. */
	for (i = 0; i <= n-1; i++)
	   B[i] = MDPROD(p,ap,A[i]);
	B[n] = 1;

Return: /* Return B. */
	return(B);
}
