/*====================================================================
		      J <- IPIIRB(A,I,t,k)

Integral polynomial isolating interval refinement - bisection.

Inputs
  A:  in Z[x], squarefree.
  I:  a logarithmic open or one-point standard interval for
      a root \alpha of A.
  t:  the trend of I.
  k:  a BETA-integer.

Output
  J:  a logarithmic open or one-point standard isolating
      subinterval of I of width 2^{k} or less.
=====================================================================*/
#include "saclib.h"

Word IPIIRB(A,I,t,k)
       Word A,I,t,k;
{
       Word  a,b,c,h,J,s;

Step1: /* Decompose. */
       FIRST2(I,&a,&b);

Step2: /* One-point interval. */
       if (EQUAL(a,b) == 1)
	  goto Step5;

Step3: /* Width of I. */
       h = LSILW(I);

Step4: /* Bisect as needed. */
       while (h > k) {
	  c = LSIM(a,b);
	  s = IUPBRES(A,c);
	  if (s == 0) {
	     a = c;
	     b = c;
	     goto Step5; }
	  if (s == t)
	     b = c;
	  else
	     a = c;
	  h--; }

Step5: /* Compose. */
       J = LIST2(a,b);

Return: /* Return. */
       return(J);
}
