/*=====================================================================
			   RIWRITE(I)

Rational interval write.

Input
   I : an interval with rational number endpoints.

Side effect
   The interval I is written in the output stream.  Let
   a and b be the left and right endpoints of I,
   respectively.  If a = b, the form of the output is
   [a].  If a < b, the form of the output is (a,b).  
   a and b are written as rational numbers using RNWRITE.
======================================================================*/
#include "saclib.h"

void RIWRITE(I)
       Word I;
{
       Word a,b;

Step1: /* One point or open interval? */
       FIRST2(I,&a,&b);
       if (EQUAL(a,b)) {
	  CWRITE('[');
	  RNWRITE(a);
	  CWRITE(']'); }
       else {
	  CWRITE('(');
	  RNWRITE(a);
	  CWRITE(',');
	  RNWRITE(b);
	  CWRITE(')'); }

Return: /* Return */
       return;
}
