/*===========================================================================
			      B <- MUPDER(m,A)

Modular univariate polynomial derivative.

Inputs
  A : in Z/(m)[X].
  m : a BETA-digit.

Outputs
  B : in Z/(m)[X], the derivative of A.
===========================================================================*/
#include "saclib.h"

Word MUPDER(m,A)
       Word m,A;
{
       Word Ap,B,a,e;

Step1: /* A = 0. */
       if (A == 0) {
	  B = 0;
	  goto Return; }

Step2: /* A /= 0. */
       B = NIL;
       Ap = A;
       do {
	  ADV2(Ap,&e,&a,&Ap);
	  a = MDPROD(m,e,a);
	  if (a != 0) {
	     e = e - 1;
	     B = COMP2(a,e,B); } }
       while (Ap != NIL);
       if (B == NIL)
	  B = 0;
       else
	  B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
