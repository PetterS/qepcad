/*======================================================================
                      	q = GINQ(a,b)

Gaussian integer nearest quotient.

Inputs
   a, b : Gaussian integers, b /= 0.

Output
   q : the nearest quotient to a / b, a Gaussian integer.
======================================================================*/
#include "saclib.h"

Word GINQ(a,b)
	Word a,b;
{
	Word ap,ap1,ap2,bp,c,q1,q2,q;

Step1: /* Compute. */
	bp = GICONJ(b);
	ap = GIPROD(a,bp);
	c = GINORM(b);
	FIRST2(ap, &ap1,&ap2);
	q1 = INQ(ap1,c);
	q2 = INQ(ap2,c);
	if (q1 == 0 && q2 == 0)
	   q = 0;
	else
	   q = LIST2(q1,q2);

Return: /* return q. */
	return(q);
}
