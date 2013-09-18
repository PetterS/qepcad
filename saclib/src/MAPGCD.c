/*===========================================================================
                      C <- MAPGCD(p,A,B)

Modular array polynomial greatest common divisor.

Inputs
   p : a prime beta digit.
   A,B : modular array polynomials over Z_p, both non-zero.

Outputs
   C : the greatest common divisor of A and B, a modular array
       polynomial over Z_p.
===========================================================================*/
#include "saclib.h"

Word *MAPGCD(p,A,B)
	BDigit p;
	Word *A,*B;
{
	Word *C,*D,*E,*T;

Step1: /* Copy A and B to D and E. */
	D = MAPCOPY(A);
	E = MAPCOPY(B);

Step2: /*  Compute remainders. */
 	do {
	   while (MAPDEG(D) >= MAPDEG(E))
	      MAPRS(p,D,E);
	   T = D;
	   D = E;
	   E = T; }
	while (MAPDEG(E) > 0);

Step3: /* Make the result monic. */
	if (MAPZERO(E))
	  C = MAPMON(p,D);
	else 
	  C = MAPMON(p,E);

Step4: /* Free arrays. */
	MAPFREE(D);
	MAPFREE(E);

Return: /* Return C. */
	return(C);
}
