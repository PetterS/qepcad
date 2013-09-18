/*======================================================================
                      n <- IUPVAR(A)

Integral univariate polynomial variations.

Inputs
  A : in Z[X], non-zero.

Outputs
  n : the number of sign variations in the coefficients of A.
======================================================================*/
#include "saclib.h"

Word IUPVAR(A)
       Word A;
{
       Word Ap,a,e,n,s,t;
       /* hide algorithm */

Step1: /* Compute. */
       n = 0;
       Ap = A;
       ADV2(Ap,&e,&a,&Ap);
       s = ISIGNF(a);
       while (Ap != NIL)
         {
         ADV2(Ap,&e,&a,&Ap);
         t = ISIGNF(a);
         if (s != t)
           {
           n = n + 1;
           s = t;
           }
         }

Return: /* Prepare for return. */
       return(n);
}
