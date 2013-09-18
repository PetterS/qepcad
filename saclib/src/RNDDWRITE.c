/*======================================================================
                      RNDDWRITE(R,n,t)

Rational number directed decimal write. 

Inputs
   R : a rational number.  
   n : a non-negative BETA-digit.  
   t : +1 or -1, an BETA-digit.

Side effects
   R is approximated by a decimal fraction d with n decimal digits 
   following the decimal point and d is written in the output stream.  
   The inaccuracy of the approximation is less than 10^{-n}.  
   If  t = -1 then d <= R;  if t = +1 then d >= R.  If |d| > |R|
   the last digit is followed by a '-'; and if |d| < |R| it is
   followed by a '+'.
======================================================================*/
#include "saclib.h"

void RNDDWRITE(R,n,t)
       Word R,n,t;
{
       Word A,B,D,F,G,M,d,i,s;

Step1: /* Compute decimal approximation. */
       if (R == 0) {
	  A = 0;
	  B = 1; }
       else
	  FIRST2(R,&A,&B);
       s = ISIGNF(A);
       if (s < 0)
	  A = INEG(A);
       M = IEXP(10,n);
       A = IPROD(A,M);
       IQR(A,B,&D,&F);
       if (F != 0 && s == t)
	  D = ISUM(D,1);

Step2: /* Convert and write. */
       if (s < 0)
	  CWRITE('-');
       IQR(D,M,&D,&G);
       IWRITE(D);
       CWRITE('.');
       for (i = 1; i <= n; i++) {
	  G = IDPR(G,10);
	  IQR(G,M,&d,&G);
	  CWRITE(d + '0'); }
       if (F != 0) {
	  if (s != t)
	     CWRITE('+');
	  else
	     CWRITE('-'); }

Return: /* Prepare for return. */
       return;
}
