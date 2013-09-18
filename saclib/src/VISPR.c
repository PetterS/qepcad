/*======================================================================
                      C <- VISPR(a,A)

Vector of integers scalar product.

Inputs
  a : in Z.
  A : a vector over Z.

Outputs
  C : a vector over Z, C = aA.
======================================================================*/
#include "saclib.h"

Word VISPR(a,A)
       Word a,A;
{
       Word Ap,C,ap,c,i,n;
       /* hide Ap,ap,i,n; */

Step1: /* a=0. */
       if (a == 0)
         {
         n = LENGTH(A);
         C = NIL;
         for (i = 1; i <= n; i++)
           C = COMP(0,C);
         goto Return;
         }

Step2: /* a=1. */
       if (a == 1)
         {
         C = A;
         goto Return;
         }

Step3: /* a=-1. */
       if (a == -1)
         {
         C = VINEG(A);
         goto Return;
         }

Step4: /* General case. */
       C = NIL;
       Ap = A;
       do
         {
         ADV(Ap,&ap,&Ap);
         c = IPROD(a,ap);
         C = COMP(c,C);
         }
       while (Ap != NIL);
       C = INV(C);

Return: /* Prepare for return. */
       return(C);
}
