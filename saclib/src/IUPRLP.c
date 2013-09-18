/*======================================================================
                      r <- IUPRLP(A)

Integral univariate polynomial, root of a linear polynomial.

Inputs
  A : in Z[X], deg(A) = 1.

Outputs
  R : the unique rational number such that A(r)=0.
======================================================================*/
#include "saclib.h"

Word IUPRLP(A)
       Word A;
{
       Word L,a,b,r;

Step1: /* Compute. */
       if (PRED(A) == 0)
         r = 0;
       else
         {
         L = PCL(A);
         FIRST2(L,&a,&b);
         r = RNRED(INEG(b),a);
         goto Return;
         }

Return: /* Prepare for return. */
       return(r);
}
