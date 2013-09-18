/*======================================================================
			t <- IUPVART(A)

Integral univariate polynomial variation test.

Inputs
  A : in Z[x], non-zero.

Outputs
  t : t = 1 if A has at least one sign variation; otherwise t = 0.
======================================================================*/
#include "saclib.h"

Word IUPVART(A)
       Word A;
{
       Word Ap,a,e,s,t,u;

Step1: /* Compute. */
       Ap = A;
       ADV2(Ap,&e,&a,&Ap);
       s = ISIGNF(a);
       t = 0;
       while (Ap != NIL) {
	  ADV2(Ap,&e,&a,&Ap);
	  u = ISIGNF(a);
	  if (u != s) {
	     t = 1;
	     goto Return; } }

Return: /* Prepare for return. */
       return(t);
}
