/*======================================================================
                      RIDWRITE(I,n)

Rational interval decimal write. 

Inputs
   I : an open or one-point interval with rational number
       endpoints.  
   n : a non-negative integer.  

Side effects
   if I is an open interval, the endpoints of I are 
   approximated by n-decimal-digit fractions and printed, 
   using RNDDWRITE.  The left endpoint is rounded down,
   the right endpoint up.  If I is a one-point interval,
   its one point is printed using RNDWRITE, which rounds
   it to the nearest n-digit decimal fraction.
======================================================================*/
#include "saclib.h"

void RIDWRITE(I,n)
       Word I,n;
{
       Word a,b;

Step1: /* I a one-point interval. */
       FIRST2(I,&a,&b);
       if (EQUAL(a,b)) {
	  CWRITE('[');
	  RNDWRITE(a,n);
	  CWRITE(']');
	  goto Return; }

Step2: /* I an open interval. */
       CWRITE('(');
       RNDDWRITE(a,n,-1);
       CWRITE(',');
       RNDDWRITE(b,n,1);
       CWRITE(')');

Return: /* Return. */
       return;
}
