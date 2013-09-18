/*===========================================================================
			       b <- AFNEG(a)

Algebraic number field negation.

Input
 a : in Q(alpha).

Output
 b : in Q(alpha), b = -a.
===========================================================================*/
#include "saclib.h"

Word AFNEG(a)
       Word a;
{
       Word A,b,r;

Step1: /* Change sign. */
       if (a == 0) {
	  b = 0;
	  goto Return; }
       FIRST2(a,&r,&A);
       b = LIST2(RNNEG(r),A);

Return: /* Prepare for return. */
       return(b);
}
