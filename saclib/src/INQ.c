/*=======================================================================
                               q = INQ(a,b)

Integer nearest quotient.

Inputs
   a, b: integers, b > 0.

Output
   q   : the nearest integer to a / b.
=======================================================================*/
#include "saclib.h"

Word INQ(a,b)
	Word a,b;
{
	Word ap,q,r;
	BDigit s,t;

Step1: /* a = 0? */
	if (a == 0) {
	   q = 0;
	   goto Return; }

Step2: /* Division with remainder. */
	s = ISIGNF(a);
	ap = IABSF(a);
	IQR(ap,b, &q,&r);

Step3: /* Adjust q if needed. */
	r = IMP2(r,1);
	t = ICOMP(b,r);
	if (t < 0 || (t == 0 && IODD(q))) 
	   q = ISUM(q,1);

Step4: /* Restore sign. */
	if (s < 0)
	   q = INEG(q);

Return: /* Return q. */
	return(q);
}
