/*======================================================================
                      B <- PDBORD(A)

Polynomial divided by order.

Inputs
  A : a non-zero polynomial.

Outputs
  B : polynomial B(X) = A(X)/X^k where k is the order of A.
======================================================================*/
#include "saclib.h"

Word PDBORD(A)
       Word A;
{
       Word Ap,B,a,e,k;
       /* hide Ap,a,e,k; */

Step1: /* Compute. */
       k = PORD(A);
       if (k == 0)
         B = A;
       else
         {
         B = NIL;
         Ap = A;
         do
           {
           ADV2(Ap,&e,&a,&Ap);
           e = e - k;
           B = COMP2(a,e,B);
           }
         while (!(Ap == NIL));
         B = INV(B);
         }

Return: /* Prepare for return. */
       return(B);
}
