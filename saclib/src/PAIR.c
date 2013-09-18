/*======================================================================
                      C <- PAIR(A,B)

Pair.

Inputs
  A,B : lists, A=(a1,...,am) and B=(b1,...,bn), n >= 0, m >= 0.

Outputs
  C   : the list (a1,b1,...,ar,br), where r=min(m,n).
======================================================================*/
#include "saclib.h"

Word PAIR(A,B)
       Word A,B;
{
       Word Ap,Bp,C,a,b;
       /* hide Ap,Bp,a,b; */

Step1: /* Compute. */
       Ap = A;
       Bp = B;
       C = NIL;
       while (Ap != NIL && Bp != NIL)
         {
         ADV(Ap,&a,&Ap);
         ADV(Bp,&b,&Bp);
         C = COMP2(b,a,C);
         }
       C = INV(C);

Return: /* Prepare for return. */
       return(C);
}
