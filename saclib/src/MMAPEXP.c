/*===========================================================================
		      B <- MMAPEXP(m,A,n)

Medium modulus array polynomial exponentiation.

Inputs
  m : a medium BETA-digit.
  A : in Z/(m)[x], in array representation, and ldcf(A) is a unit.
  n : a non-negative BETA-digit.

Output
  B : in Z/(p), B = x^n modulo A(x).  B is in array representation.
===========================================================================*/
#include "saclib.h"

Word *MMAPEXP(m,A,n)
       Word m,*A,n;
{
       Word d,*B,i,k,*C;

Step1: /* Get array B. */
       d = MAPDEG(A);
       B = MAPGET(2 * (d - 1));

Step2: /* n < d. */
       if (n < d) { 
	  MAPDEG(B) = n;
	  MAPCF(B,n) = 1;
	  for (i = 0; i < n; i++)
	     MAPCF(B,i) = 0;
	  goto Return; }

Step3: /* n >= d. */
       k = n / 2; 
       C = MMAPEXP(m,A,k); 
       MMAPPROD(m,C,C,B);
       MAPFREE(C); 
       MMAPREM(m,B,A); 
       if (ODD(n)) {
	  MAPMPV(B,1);
	  MMAPREM(m,B,A); }

Return: /* Prepare for return. */
       return(B);
}
