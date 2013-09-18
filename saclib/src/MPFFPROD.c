/*=======================================================================
                         C <- MPFFPROD(p,F,A,B)

Medium prime finite field product.

Inputs
   p : a medium prime.
   F : an irreducible monic polynomial over Z_p in array representation
       of degree n defining a finite field Gf(p^n).
   A, B : elements of GF(p^n) in array representation.

Output
   C : C = A * B, an element of GF(p^n) in array representation.
=======================================================================*/
#include "saclib.h"

BDigit *MPFFPROD(p,F,A,B)
	BDigit p,*F,*A,*B;
{
	BDigit *C,n,*P;

Step1: /* Get array for product. */
	n = MAPDEG(F);
	P = MAPGET(n + n);

Step2: /* Compute product in Z_p[x]. */
	MMAPPROD(p,A,B,P);

Step3: /* Reduce product modulo F. */
	MMAPREM(p,P,F);

Step4: /* Copy result to a smaller array. */
	C = MAPCOPY(P);
	MAPFREE(P);

Return: /* Return C. */
	return(C);
}
