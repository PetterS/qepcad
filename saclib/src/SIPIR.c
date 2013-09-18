/*======================================================================
                   J <- SIPIR(A,I,t,k)

Software interval polynomial interval refinement.

Inputs
   A : a software interval polynomial of positive degree n
       containing a real polynomial a(x) of degree n.
   I : an open or one-point standard logarithmic binary rational
       isolating interval for a simple root alpha of a(x).
   t : the trend of alpha.
   k : a BETA-integer.

Output
   J : a standard logarithmic binary rational sub-interval of I
       that is an isolating interval for alpha.  If the width
       of I is less than or equal to 2^k, then J = I.  
       Otherwise J is either a one-point interval or else the
       width of J is either 2^k or else wider but as small as
       could be achieved.
======================================================================*/
#include "saclib.h"

Word SIPIR(A,I,t,k)
        Word *A,I;
	BDigit t,k;
{
        Word a,b,*C,c,J,s;
	BDigit h,m,p,q;

Step1: /* Decompose. */
       FIRST2(I,&a,&b);

Step2: /* Width of interval. */
       if (EQUAL(a,b) == 1)
	  goto Step6;
       else
	  h = LSILW(I);

Step3: /* Allocate midpoint. */
       p = 1;
       C = GETARRAY(p+3);

Step4: /* Bisect as needed. */
       while (h > k) {
	  c = LSIM(a,b);
	  m = ILOG2(FIRST(c)) + ZETA - 1;
	  q = m / ZETA;
	  if (q > p) {
	    FREEARRAY(C);
	    C = GETARRAY(q+3);
	    p = q; }
	  LBRNFEC(c,q,C);
	  s = SIPES(A,C);
	  if (s == NIL)
	    goto Step5;
	  if (s == 0) {
	    a = c;
	    b = c;
	    goto Step5; }
	  if (s == t)
	    b = c;
	  else
	    a = c;
	  h--; }

Step5: /* Free midpoint. */
       FREEARRAY(C);

Step6: /* Compose. */
       J = LIST2(a,b);

Return: /* Return. */
       return(J);
}
