/*===========================================================================
			       n <- IORD2(A)

Integer, order of 2.  

Inputs
  A : in Z, A not 0.  

Outputs
  n : the largest integer n such that 2^n divides A.
===========================================================================*/
#include "saclib.h"

Word IORD2(A)
       Word A;
{
       Word a,Ap,n;

Step1: /* Count low-order BETA-digits. */
       n = 0;
       if (A < BETA)
	  a = A;
       else {
	  Ap = A;
	  while (FIRST(Ap) == 0) {
	     Ap = RED(Ap);
	     n = n + ZETA; }
	  a = FIRST(Ap); }

Step2: /* Count low-order bits. */
       a = absm(a);
       while ((a & 01) == 0) {
	  a = a >> 1;
	  n = n + 1; }

Return: /* Prepare for return. */
       return(n);
}
