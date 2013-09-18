/*=====================================================================
                      u <- LBRNCOMP(A,B)

Logarithmic binary rational number comparison.

Inputs
   A, B : logarithmic binary rational numbers.

Outputs
   u    : sign(A - B), an integer.
======================================================================*/
#include "saclib.h"

Word LBRNCOMP(A,B)
       Word A,B;
{
       Word a,b,e,f,s,t,u;

Step1: /* A = 0 or B = 0. */
       if (A == 0) {
	  u = -LBRNSIGN(B);
	  goto Return; }
       if (B == 0) {
	  u = LBRNSIGN(A);
	  goto Return; }

Step2: /* Disassemble A and B. */
       FIRST2(A,&a,&e);
       FIRST2(B,&b,&f);

Step3: /* A and B have opposite signs. */
       s = ISIGNF(a);
       t = ISIGNF(b);
       if (s != t) {
	  u = s;
	  goto Return; }

Step4: /* A and B have the same sign. */
       if (e < f)
	  u = ICOMP(IMP2(a,f - e),b);
       else if (e > f)
	  u = ICOMP(a,IMP2(b,e - f));
       else
	  u = ICOMP(a,b);

Return: /* Return u. */
       return(u);
}
