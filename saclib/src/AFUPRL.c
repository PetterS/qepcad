/*======================================================================
                      a <- AFUPRL(M,A)

Algebraic number field univariate polynomial, root of a linear polynomial.  

Inputs
  M : in Z[x], the minimal polynomial for an algebraic number alpha.
  A : in Q(alpha)[x]. deg(A) = 1.

Outputs
  a : in Q(alpha). a is the unique element of Q(alpha) such
      that A(a) = 0.
======================================================================*/
#include "saclib.h"

Word AFUPRL(M,A)
       Word M,A;
{
       Word L,a,c,d;
       /* hide c,d; */

Step1:
       if (PRED(A) == 0)
         a = 0;
       else
         {
         L = PCL(A);
         FIRST2(L,&c,&d);
         a = AFQ(M,AFNEG(d),c);
         }

Return: /* Prepare for return. */
       return(a);
}
