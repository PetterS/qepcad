/*======================================================================
                      L <- PCL(A)

Polynomial coefficient list.

Inputs
  A : a non-zero polynomial.

Outputs
  L : the list (an,a_{n-1},...,a0) where n = deg(A) and
      A(x) = an X^n + a_{n-1} X^{n-1} +...+ a0.
======================================================================*/
#include "saclib.h"

Word PCL(A)
       Word A;
{
       Word Ap,L,a,e,m,n;
       /* hide Ap,a,e,m,n; */

Step1: /* Compute. */
       Ap = A;
       n = FIRST(Ap);
       L = NIL;
       for (m = n; m >= 0; m--)
         {
         if (Ap == NIL)
           e = -1;
         else
           e = FIRST(Ap);
         if (e == m)
           ADV2(Ap,&e,&a,&Ap);
         else
           a = 0;
         L = COMP(a,L);
         }
       L = INV(L);

Return: /* Prepare for return. */
       return(L);
}
