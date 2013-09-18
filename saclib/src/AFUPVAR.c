/*======================================================================
                      n <- AFUPVAR(M,I,A)

Algebraic number field univariate polynomial variations.  

Inputs
  M : in Z[x], the minimal polynomial for an algebraic number alpha.
  I : a binary rational interval. I is an acceptable isolating interval for 
      alpha.
  A : in Q(alpha)[x], A not zero.

Outputs
  n : a BETA-digit, n = var(A).
======================================================================*/
#include "saclib.h"

Word AFUPVAR(M,I,A)
       Word M,I,A;
{
       Word Ap,a,e,n,s,t;
       /* hide n,s,t; */

Step1:
       n = 0;
       Ap = A;
       ADV2(Ap,&e,&a,&Ap);
       s = AFSIGN(M,I,a);
       while (Ap != NIL)
         {
         ADV2(Ap,&e,&a,&Ap);
         t = AFSIGN(M,I,a);
         if (s != t)
           {
           n = n + 1;
           s = t;
           }
         }

Return: /* Prepare for return. */
       return(n);
}
