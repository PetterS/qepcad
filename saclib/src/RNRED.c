/*===========================================================================
			      R <- RNRED(A,B)

Rational number reduction to lowest terms.  

Inputs
  A,B : integers, B non-zero.  

Outputs
  R   : the rational number A/B in canonical form.
===========================================================================*/
#include "saclib.h"

Word RNRED(A,B)
       Word A,B;
{
       Word Ab,Bb,C,R;

Step1: /* Compute. */
       if (A == 0) {
	  R = 0;
	  goto Return; }
       C = IGCD(A,B);
       Ab = IEQ(A,C);
       Bb = IEQ(B,C);
       if (ISIGNF(B) < 0) {
	  Ab = INEG(Ab);
	  Bb = INEG(Bb); }
       R = LIST2(Ab,Bb);

Return: /* Prepare for return. */
       return(R);
}
