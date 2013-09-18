/*=====================================================================
                      T <- LBRNSUM(R,S)

Logarithmic binary rational number sum.

Inputs
   R, S : logarithmic binary rational numbers.

Outputs
   T    : R + S, a logarithmic binary rational number.
======================================================================*/
#include "saclib.h"

Word LBRNSUM(R,S)
       Word R,S;
{
       Word a,b,c,e,f,k,T;

Step1: /* R=0 or S=0. */
       if (R == 0) {
	  T = S;
	  goto Return; }
       if (S == 0) {
	  T = R;
	  goto Return; }

Step2: /* Disassemble R and S. */
       FIRST2(R,&a,&e);
       FIRST2(S,&b,&f);

Step3: /* Compute sum. */
       if (e < f) {
	  c = ISUM(IMP2(a,f - e),b);
	  T = LIST2(c,f); }
       else if (e > f) {
	  c = ISUM(a,IMP2(b,e - f));
	  T = LIST2(c,e); }
       else {
	  c = ISUM(a,b);
	  if (c == 0) 
	     T = 0;
	  else {
	     k = IORD2(c);
	     c = IDP2(c,k);
	     T = LIST2(c, e - k); } }

Return: /* Return T. */
	return(T);
}
