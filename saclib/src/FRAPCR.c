/*==========================================================================
			Ap <- FRAPCR(A)

Finite ring array polynomial convert representation.

Inputs
  A : in (Z/(p)[x])/(M)[y], A is in array representation.

Outputs
  Ap : in (Z/(p)[x])/(M)[y], Ap = A, with Ap in list representation.
==========================================================================*/
#include "saclib.h"

Word FRAPCR(A)
       Word **A;
{
       Word Ap,i,n,c;
       
Step1: /* A = NIL. */
       if (FRAPDEG(A) < 0) {
	  Ap = NIL;
	  goto Return; }

Step2: /* Convert to list. */
       Ap = 0;
       n = FRAPDEG(A);
       for (i = 0; i <= n; i++) {
	  c = MUPFMAP(FRAPCF(A,i));
	  Ap = PPLT(i,c,Ap); }

Return: /* Prepare for return. */
       return(Ap);
}
