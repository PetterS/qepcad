/*======================================================================
                           RSI(p,a,b,I)

Ratio to software interval.

Inputs
   p : a positive BETA-digit (precision).
   a : a nonzero integer.
   b : a positive integer.
   I : an array of size (at least) 2 p + 6.

Effect
   Nearly the smallest software interval of precision p containing
   a / b is computed and stored in I.
======================================================================*/
#include "saclib.h"

void RSI(p,a,b,I)
	BDigit p;
	Word a,b;
	BDigit *I;
{
	BDigit *A,*B,q;

Step1: /* Get arrays. */
	q = 2 * p + 6;
	A = GETARRAY(q);
	B = GETARRAY(q);
	
Step2: /* Convert a and B to intervals. */
	ISI(a,p,A);
	ISI(b,p,B);

Step3: /* Divide. */
        SIQUOT(A,B,I);

Step4: /* Free arrays. */
	FREEARRAY(A);
	FREEARRAY(B);

Return: /* Return. */
	return;
}
