/*======================================================================
                    	b <- GIRP(a)

Gaussian integer reduced part.

Input
   a : a nonzero Gaussian integer.

Output
   b : a greatest divisor of a that is not divisible by 1 + i.
======================================================================*/
#include "saclib.h"

Word GIRP(a)
	Word a;
{
	Word a1,a2,b1,b2,b;
	BDigit s1,s2;

Step1: /* Division loop. */
	FIRST2(a, &a1,&a2);
	do {
	   s1 = IEVEN(a1);
	   s2 = IEVEN(a2);
	   if (s1 != s2)
	      goto Step2;
	   if (s1 == 1) {
	      a1 = IQ(a1,2);
	      a2 = IQ(a2,2); }
	   else {
	      b1 = ISUM(a1,a2);
	      b2 = IDIF(a2,a1);
	      a1 = IQ(b1,2);
	      a2 = IQ(b2,2); } }
	while (1);

Step2: /* Compose. */
	b = LIST2(a1,a2);

Return: /* Return b. */
	return(b);
}
