/*======================================================================
                             B <- FLBRN(F)

Floating point to logarithmic binary rational number conversion.

Inputs
   F : a software floating point number.

Outputs
   B : a logarithmic binary rational number, B = F.
======================================================================*/
#include "saclib.h"

Word FLBRN(F)
        BDigit *F;
{
        BDigit e,f,i,n,s,p;
        Word A,B;

Step1: /* F = 0. */
       if (F[1] == 0) {
         B = 0;
         goto Return; }

Step2: /* Get exponent, sign and precision. */
	e = F[0];
	s = F[1];
	p = F[2];

Step3: /* Convert mantissa to an integer A. */
	if (p == 1)
	   A = F[3];
	else {
	   A = NIL;
	   for (i = p + 2; i >= 3; i--)
	      A = COMP(F[i],A); }

Step4: /* Divide A by the largest possible power of 2. */
	n = IORD2(A);
	A = IDP2(A,n);

Step5: /* Make A negative? */
	if (s < 0)
	   A = INEG(A);

Step6: /* Compute the base 2 logarithm of the denominator. */
	f = p * ZETA - n - e;

Step7: /* Compose B. */
	B = LIST2(A,f);

Return: /* Return B. */
        return(B);
}
