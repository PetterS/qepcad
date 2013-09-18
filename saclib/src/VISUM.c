/*======================================================================
                      C <- VISUM(A,B)

Vector of integers sum.

Inputs
  A,B : vectors over Z.

Outputs
  C   : a vector over Z, C = A+B.
======================================================================*/
#include "saclib.h"

Word VISUM(A,B)
       Word A,B;
{
       Word Ap,Bp,C,a,b,c;
       /* hide Ap,Bp,a,b; */

Step1: /* Compute. */
       C = NIL;
       Ap = A;
       Bp = B;
       do
         {
         ADV(Ap,&a,&Ap);
         ADV(Bp,&b,&Bp);
         c = ISUM(a,b);
         C = COMP(c,C);
         }
       while (Ap != NIL);
       C = INV(C);

Return: /* Prepare for return. */
       return(C);
}
