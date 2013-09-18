/*===========================================================================
			C <- RNROUND(R)

Rational number rounding.

Input
  R : a rational number.

Output
  C : an integer obtained by rounding r to the nearest integer,
      using round-to-even to break ties.
===========================================================================*/
#include "saclib.h"

Word RNROUND(R)
       Word R;
{
       Word A,B,C,R1,R2,s,t;

Step1: /* R = 0. */
       if (R == 0) {
	  C = 0;
	  goto Return; }

Step2: /* R /= 0. */
       R1 = RNNUM(R);
       R2 = RNDEN(R);
       IQR(R1,R2,&A,&B);
       s = ISIGNF(R1);
       if (s > 0)
	  B = IPROD(2,B);
       else
	  B = IPROD(2,INEG(B));
       t = ICOMP(B,R2);
       if (t < 0)
	  C = A;
       else if (t > 0)
	  C = ISUM(A,s);
       else
	  if (EVEN(A))
	     C = A;
	  else
	     C = ISUM(A,s);

Return: /* Prepare for return. */
       return(C);
}
