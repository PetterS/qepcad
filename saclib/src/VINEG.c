/*======================================================================
                      B <- VINEG(A)

Vector of integers negation.

Inputs
  A : a vector over Z.

Outputs
  B : a vector over Z, B = -A.
======================================================================*/
#include "saclib.h"

Word VINEG(A)
       Word A;
{
       Word Ap,B,a,b;
       /* hide Ap,a; */

Step1: /* Compute. */
       B = NIL;
       Ap = A;
       do
         {
         ADV(Ap,&a,&Ap);
         b = INEG(a);
         B = COMP(b,B);
         }
       while (Ap != NIL);
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
