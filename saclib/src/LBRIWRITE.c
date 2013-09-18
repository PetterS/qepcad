/*=====================================================================
			  LBRIWRITE(I)

Logarithmic binary rational interval write.

Input
   I : a logarithmic binary rational interval in internal
       representation. I is the list (<a>,<b>) consisting of
       the logarithmic representations of the binary rational 
       endpoints a and b of the interval.
       If a = b, I represents the one-point interval [a].
       Otherwise, a < b and I represents the open interval (a,b).

Outputs (to the output stream)
  Canonical external representation of I.
  If I is the one-point interval [a], the output is [<a>] where
  <a> is the canonical external representation of a.
  If I is the open interval (a,b), the output is
    (<a>,<b>)
  where
  <a> and <b> are the canonical external representations of a and b.

Side effect
   The interval I is written in the output stream.
======================================================================*/
#include "saclib.h"

void LBRIWRITE(I)
       Word I;
{
       Word a,b;

Step1: /* Two cases. */
       FIRST2(I,&a,&b);
       if (EQUAL(a,b)) {
	  CWRITE('[');
	  LBRNWRITE(a);
	  CWRITE(']'); }
       else {
	  CWRITE('(');
	  LBRNWRITE(a);
	  CWRITE(',');
	  LBRNWRITE(b);
	  CWRITE(')'); }

Return: /* Return */
       return;
}
