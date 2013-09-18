/*======================================================================
                      B <- BERNOULLINUM(n)

Bernoulli numbers via tangent numbers.

Inputs
  n : a non-negative BETA-digit.

Outputs
  B : a list of rational numbers, B = (B_0,...,B_n) where
      B_i is the i-th Bernoulli number.
======================================================================*/
#include "saclib.h"

Word BERNOULLINUM(n)

     BDigit n;
{
     Word B,b,T,t;
     BDigit m,s;

Step1: /* n = 0. */
     if (n == 0) {
       B = LIST1(RNINT(1));
       goto Return; }

Step2: /* n = 1. */
     if (n == 1) {
       B = LIST2(RNINT(1),RNNEG(RNRED(1,2)));
       goto Return; }

Step3: /* Tangent numbers. */
       T = TANGENTNUM(n);

Step4: /* Bernoulli numbers. */
       T = RED(T);
       B = LIST2(RNNEG(RNRED(1,2)),RNINT(1));
       m = 2;
       s = 1;
       for (m = 2; m <= n; m++) {
	 ADV(T,&t,&T);
	 if (t == 0)
	   b = 0;
	 else {
	   b = RNRED(IDPR(t,m),IMP2(IDIF(IMP2(1,m),1),m));
	   if (s == -1)
	     b = RNNEG(b);
	   s = -s; }
	 B = COMP(b,B); }

Step5: /* Invert. */
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}


