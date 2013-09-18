/*===========================================================================
                             C <- MUPGCD(p,A,B)

Modular univariate polynomial greatest common divisor.

Inputs
   p : a prime beta digit.
   A, B : modular univariate polynomials over Z_p.

Output
   C : the monic greatest common divisor of A and B.
===========================================================================*/
#include "saclib.h"

Word MUPGCD(p,A,B)
	BDigit p;
	Word A,B;
{
	BDigit *Ap,*Bp,*Cp;
	Word C;

Step1: /* A = 0 or B = 0. */
	if (A == 0) {
	   C = B;
	   goto Return; }
	if (B == 0) {
	   C = A;
	   goto Return; }

Step2: /* deg(A) = 0 or deg(B) = 0. */
	if (PDEG(A) == 0 || PDEG(B) == 0) {
	   C = LIST2(0,1);
	   goto Return; }
	   

Step3: /* Convert inputs to array representation. */
	Ap = MAPFMUP(A);
	Bp = MAPFMUP(B);

Step4: /* Apply MAPGCD. */
	Cp = MAPGCD(p,Ap,Bp);

Step5: /* Convert result to list representation. */
	C = MUPFMAP(Cp);

Step6: /* Free arrays. */
	MAPFREE(Ap);
	MAPFREE(Bp);
	MAPFREE(Cp);

Return: /* Return C. */
	return(C);
}
