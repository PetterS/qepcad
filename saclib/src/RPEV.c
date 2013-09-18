/*===========================================================================
			    B <- RPEV(r,A,i,a)

Rational polynomial evaluation.  

Inputs
  r : a positive BETA-digit.
  A : in Q[x_1,...,x_r].
  i : a BETA-digit, 1 <= i <= r.
  a : in Q.
  
Output
  B : in Q[x_1,...,x_{i-1},x_{i+1},...,x_r], the result of evaluating
      A at x_i = a.
===========================================================================*/
#include "saclib.h"

Word RPEV(r,A,i,a)
       Word r,A,i,a;
{
       Word A1,Ap,B,B1,e1,rp;

Step1: /* A = 0. */
       if (A == 0) {
	  B = 0;
	  goto Return; }

Step2: /* i = r. */
       if (i == r) {
	  B = RPEMV(r,A,a);
	  goto Return; }

Step3: /* i < r. */
       rp = r - 1;
       Ap = A;
       B = NIL;
       do {
	  ADV2(Ap,&e1,&A1,&Ap);
	  B1 = RPEV(rp,A1,i,a);
	  if (B1 != 0)
	     B = COMP2(B1,e1,B); }
       while (Ap != NIL);
       B = INV(B);
       if (B == NIL)
	  B = 0;

Return: /* Prepare for return. */
       return(B);
}
