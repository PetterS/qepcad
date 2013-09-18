/*==========================================================================
			MMAPMDP(m,a,A,B)

Medium modulus array polynomial modular digit product.

Inputs
  m : a medium BETA-digit.
  a : in Z/(m).
  A : in Z/(m)[x], A is in array representation.
  B : a pointer to an array large enough to hold A.

Side effects
  B is modified to contain a*A.
==========================================================================*/
#include "saclib.h"

void MMAPMDP(m,a,A,B)
       Word m,a,*A,*B;
{
       Word i,d;
       
Step1: /* a = 0 or A = 0. */
       if (a == 0 || MAPZERO(A))  {
	  MAPDEG(B) = 0;
	  MAPLDCF(B) = 0;
	  goto Return; }

Step2: /* General case. */
       d = MAPDEG(A);
       MAPDEG(B) = d;
       for (i = 0; i <= d; i++)
	  MAPCF(B,i) = (a * MAPCF(A,i)) % m;

Return: /* Prepare for return. */
       return;
}
