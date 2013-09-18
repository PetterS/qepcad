/*======================================================================
		       b <- IUPEVAL(A,a)

Integral univariate polynomial evaluation.

Inputs
   A : a univariate integral polynomial.
   a : an integer

Outputs                          
   b : the integer A(a).
======================================================================*/
#include "saclib.h"

Word IUPEVAL(A,a)
       Word A,a;
{
       Word a2,Ap,b,e1,e2,i;

Step1: /* A = 0. */
       if (A == 0) {
	  b = 0;
	  goto Return; }

Step2: /* Apply Horner's method. */
       ADV2(A,&e1,&b,&Ap);
       while (Ap != NIL) {
	  ADV2(Ap,&e2,&a2,&Ap);
	  for (i = 1; i <= e1 - e2; i++)
	     b = IPROD(a,b);
	  b = ISUM(b,a2);
	  e1 = e2; }
       for (i = 1; i <= e1; i++)
	  b = IPROD(a,b);

Return: /* Return b. */
       return(b);
}
