/*======================================================================
                      A <- PBIN(a1,e1,a2,e2)

Polynomial binomial.

Inputs
  a1,a2 : in a coefficient ring R.
  e1,e2 :  non-negative BETA-digits, e1 > e2.

Outputs
  A : in R[X], A(x)=a1x^e1+a2x^e2.
======================================================================*/
#include "saclib.h"

Word PBIN(a1,e1,a2,e2)
       Word a1,e1,a2,e2;
{
       Word A;

Step1: /* Compute. */
       A = NIL;
       if (a2 != 0)
         A = LIST2(e2,a2);
       if (a1 != 0)
         A = COMP2(e1,a1,A);
       if (A == NIL)
         A = 0;

Return: /* Prepare for return. */
       return(A);
}
