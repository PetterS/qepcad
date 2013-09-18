/*======================================================================
                      e <- HEXP(a)

Hardware exponent.

Input
   a : a hardware double precision number.        

Output
   e : The exponent of a.
======================================================================*/
#include "saclib.h"

BDigit HEXP(a)
        double a;
{
	BDigit e;
	ieee b;

Step1: /* Obtain exponent. */
	b.num = a;
	e = b.rep.exp;

Return: /* Return e. */
	return(e);
}
