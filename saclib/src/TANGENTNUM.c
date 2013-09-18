/*======================================================================
                      L <- TANGENTNUM(n)

Tangent numbers.

Inputs
  n : a non-negative BETA-digit.

Outputs
  T : a list of integers, L = (T_0,...,T_n) where
      T_i is the i-th  tangent number.
======================================================================*/
#include "saclib.h"

Word TANGENTNUM(n)

     BDigit n;
{
     Word T,U,u,V,W,w;
     BDigit a,b,c,e,f,i;

Step1: /* n = 0. */
     if (n == 0) {
       T = LIST1(0);
       goto Return; }

Step2: /* n = 1. */
     if (n == 1) {
       T = LIST2(0,1);
       goto Return; }

Step3: /* Initialize. */
       T = LIST2(1,0);
       U = LIST1(0);
       a = 0;
       V = LIST2(1,1);
       b = 1;

Step4: /* Loop. */
       for (i = 2; i <= n; i++) {
	 e = a;
	 ADV(U,&u,&U);
	 w = IDPR(u,e);
	 W = LIST1(w);
	 c = a + 1;
	 f = c;
	 while (U != NIL) {
	   e--;
	   ADV(U,&u,&U);
	   w = ISUM(IDPR(u,e),IDPR(w,f));
	   W = COMP(w,W);
	   f--; }
	 w = IDPR(w,f);
	 W = COMP(w,W);
	 T = COMP(w,T);
	 U = V;
	 a = b;
	 V = INV(W);
	 b = c; }

Step5: /* Invert. */
       T = INV(T);

Return: /* Prepare for return. */
       return(T);
}


