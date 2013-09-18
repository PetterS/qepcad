/*==========================================================================
			A <- MAPFMD(a,n)

Modular array polynomial from modular digit.

Inputs
  a : an element of Z/(m), for some positive BETA-digit m.
  n : a non-negative BETA-digit.

Outputs
  A : an array large enough to hold a polynomial of degree n.
      A represents a as an element of Z/(m)[x].
==========================================================================*/
#include "saclib.h"

Word *MAPFMD(a,n)
       Word a,n;
{
       Word *A;
       
Step1: /* Get array for A. */
       A = MAPGET(n);
       
Step2: /* Initialize A. */
       MAPDEG(A) = 0;
       MAPLDCF(A) = a;
       
Return: /* Prepare for return. */
       return(A);
}
