/*=====================================================================
                         MPFFDPGT(p,n; F,G,A)

Medium prime finite field defining polynomial, generator and table.

Inputs
   p : a prime, p^2 < beta.
   n : a beta-digit, n >= 2 and p^n < beta.

Outputs
   F : a monic irreducible polynomial of degree n over Z_p
       having a minimal number of nonzero terms.
   G : a monic primitive element of Z_p/(F) of minimal degree.
   A : an array of q = p^n beta-integers.  A[0] = 0 and for 0 < i < q,
       A[i] = G^i(p).  G^i is evaluated at p in Z, not in Z_p.
=======================================================================*/
#include "saclib.h"

void MPFFDPGT(p,n,F_,G_,A)
	BDigit p,n;
	Word *F_,*G_;
	BDigit *A;
{
	BDigit *Fp,*Gp;
	Word F,G;

Step1: /* Compute a defining polynomial F. */
	F = MPFFDP(p,n);

Step2: /* Compute a generator. */
	Fp = MAPFMUP(F);
	Gp = MPFFGEN(p,Fp);
	G = MUPFMAP(Gp);

Step3: /* Generate the table. */
	A = MPFFAP(p,Fp,Gp);

Return: /* Return F, G and A. */
	*F_ = F;
	*G_ = G;
	return;
}

