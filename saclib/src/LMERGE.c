/*===========================================================================
                         C <- LMERGE(A,B)

List merge.

Inputs
  A, B  : lists of objects.

Outputs
  C  : the list obtained by merging A and B.
===========================================================================*/
#include "saclib.h"

Word LMERGE(A,B)
       Word A,B;
{
       Word Ap,Bp,C,a,b,s;

Step1: /* Compute. */
       C = A;
       Bp = B;
       while (Bp != NIL) {
         ADV(Bp,&b,&Bp);
         Ap = A;
         s = 0;
         while (Ap != NIL && s == 0) {
           ADV(Ap,&a,&Ap);
           s = EQUAL(a,b); }
         if (s == 0)
           C = COMP(b,C); }

Return: /* Prepare for return. */
       return(C);
}
