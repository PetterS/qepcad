/*===========================================================================
			      B <- AFPICR(r,A)

Algebraic number field polynomial inverse convert representation.

Inputs
  r : a non-negative BETA-integer.
  A : an element of Q(alpha)[x_1,...,x_r], where the coefficients of A are
      represented as (a_i,Ai), where a_i is an element of Q and Ai is an
      element of Z[x].

Outputs
  B : an element of Q(alpha)[x_1,...,x_r] represented as an element
      of Q[x,x_1,...,x_r].
===========================================================================*/
#include "saclib.h"

Word AFPICR(r,A)

       Word r,A;
{
       Word B;
       Word Ap,a,b,e,rp;

Step1: /* A = 0. */
       if (A == 0) {
	  B = 0;
	  goto Return; }

Step2: /* r = 0. */
       if (r == 0) {
	  B = AFICR(A);  
	  goto Return; }

Step3: /* r > 0. */
       rp = r - 1;
       Ap = A;
       B = NIL;
       while (Ap != NIL) {
	  ADV2(Ap,&e,&a,&Ap);
	  b = AFPICR(rp,a);
	  B = COMP2(b,e,B); }
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
