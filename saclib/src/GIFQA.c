/*=======================================================================
                             b = GIFQA(a)

Gaussian integer first quadrant associate.

Input
   a : a nonzero Gaussian integer.

Output
   b : b is the first quadrant associate of a.
=======================================================================*/
#include "saclib.h"

Word GIFQA(a)
	Word a;
{
	Word a1,a2,b;
	BDigit s,t;

Step1: /* Case analysis. */
	FIRST2(a, &a1,&a2);
	s = ISIGNF(a1);
	t = ISIGNF(a2);
	if (s == 1 && t >= 0) {
	   b = a;
	   goto Return; }
	if (t == 1 && s <= 0) {
	   b = LIST2(a2,INEG(a1));
	   goto Return; }
	if (s < 0 && t <= 0) {
	   b = LIST2(INEG(a1),INEG(a2));
	   goto Return; }
	b = LIST2(INEG(a2),a1);
	
Return: /* Return b. */
	return(b);
}
