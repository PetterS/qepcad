/*======================================================================
                      c <- MUPRES(p,A,B)

Modular univariate polynomial resultant.

Inputs
   p : a prime BETA-digit.
   A,B : univariate polynomials over Z_p having positive degrees.

Output
   c : the resultant of A and B, an element of Z_p.
======================================================================*/
#include "saclib.h"

Word MUPRES(p,A,B)
	BDigit p;
	Word A,B;
{

	BDigit c,d,i,k,m,n,s;
	Word *C,*D,*E, *Cp, *Dp;

Step1: /* Convert A and B to array representation. */
	Cp = C = MAPFMUP(A);
	Dp = D = MAPFMUP(B);

Step2: /* Initialize the product, c, and the sign, s. */
	c = 1;
	s = +1;
	m = MAPDEG(C);
	n = MAPDEG(D);
	if (m < n) {
	   E = C;
	   C = D;
	   D = E;
	   if (ODD(m) && ODD(n))
	      s = -1; }

Step3: /* Compute the natural PRS of A and B. */
	do {
	   m = MAPDEG(C);
	   n = MAPDEG(D);
	   if (ODD(m) && ODD(n))
	      s = -s;
	   while (MAPDEG(C) >= MAPDEG(D))
	      MAPRS(p,C,D);
	   if (MAPZERO(C)) {
	      c = 0;
	      goto Return; }
	   k = MAPDEG(C);
	   d = MAPLDCF(D);
	   for (i = 1; i <= m - k; i++)
	      c = MDPROD(p,c,d);
	   E = C;
	   C = D;
	   D = E; }
	while (k != 0);

Step4: /* Multiply by power of last leading coefficient and fix sign. */
	d = MAPLDCF(D);
	for (i = 1; i <= n; i++)
	   c = MDPROD(p,c,d);
	if (s < 0)
	   c = MDNEG(p,c);

Return: /* Return c. */
	MAPFREE(Cp);
	MAPFREE(Dp);
	return(c);
}
