/*===========================================================================
			       n <- ILOG2(A)

Integer logarithm, base 2.  

Inputs
  A : in Z.

Outputs
  n : a BETA-integer.
      If A = 0 then n = 0. 
      Otherwise, n = floor(log2(|A|))+1. 
===========================================================================*/
#include "saclib.h"

Word ILOG2(A)
       Word A;
{
       Word Ap,n;

Step1: /* A single-precision. */
       if (A < BETA) {
	  n = DLOG2(A);
	  goto Return; }

Step2: /* A multiple-precision. */
       Ap = A;
       n = 0;
       while (RED(Ap) != NIL) {
	  Ap = RED(Ap);
	  n = n + ZETA; }
       n = n + DLOG2(FIRST(Ap));

Return: /* Prepare for return. */
       return(n);
}
