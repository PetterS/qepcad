/*=======================================================================
                             c <- GIMS(a,b)

Gaussian integer minimal sum.

Inputs
   a, b :  nonzero Gaussian integers.

Output 
   c : c has minimal norm among all u a + v b such that u and v
       are units.
=======================================================================*/
#include "saclib.h"

Word GIMS(a,b)
	Word a,b;
{
	Word ap,bp,bp1,bp2,c,cp,d,dp;
	BDigit h,k,s;

Step1: /* Compute the first quadrant associates of a and b. */
	SWRITE("Entering GIMS.\n");
	SWRITE("a = ");
	GIWRITE(a);
	SWRITE("\n");
	SWRITE("b = ");
        GIWRITE(b);
        SWRITE("\n");
	ap = GIFQA(a);
	bp = GIFQA(b);

Step2: /* Compute the half-quadrants of a and b. */
	h = GIHQ(ap);
	k = GIHQ(bp);

Step3: /* h = k? */
	c = GIDIF(ap,bp);
	if (h == k)
	   goto Return;

Step4: /* h /= k. */
	FIRST2(bp, &bp1,&bp2);
	if (h < k)
	   bp = LIST2(bp2,INEG(bp1));
	else
	   bp = LIST2(INEG(bp2),bp1);
	d = GIDIF(ap,bp);
	cp = GINORM(c);
	dp = GINORM(d);
	s = ICOMP(cp,dp);
	if (s > 0)
	   c = d;

Return: /* Return c. */
	SWRITE("c = ");
        GIWRITE(c);
        SWRITE("\n");
	SWRITE("Leaving GIMS.\n");
	return(c);
}
	   
