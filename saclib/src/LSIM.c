/*======================================================================
                      c <- LSIM(a,b)

Logarithmic standard interval midpoint.

Inputs
   a, b : the endpoints of a logarithmic standard interval;
	  a < b.

Outputs
   c    : the midpoint of the interval (a,b), a logarithmic
          binary rational number.
======================================================================*/
#include "saclib.h"

Word LSIM(a,b)
       Word a,b;
{
       Word c,e,f,g,k,m,n;

Step1: /* a or b zero. */
       if (a == 0) {
	  n = FIRST(b);
	  g = SECOND(b) + 1;
	  goto Step3; }
       if (b == 0) {
	  n = FIRST(a);
	  g = SECOND(a) + 1;
	  goto Step3; }

Step2: /*  a and b non-zero. */
       FIRST2(a,&k,&e);
       FIRST2(b,&m,&f);
       if (e > f) {
	  n = ISUM(IMP2(k,1),1);
	  g = e + 1; }
       else {
	  n = IDIF(IMP2(m,1),1);
	  g = f + 1; }

Step3: /* Assemble c. */
       c = LIST2(n,g);

Return: /* Prepare for return. */
       return(c);
}
