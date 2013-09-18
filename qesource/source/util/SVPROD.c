/*======================================================================
                      C <- SVPROD(A,B)

Sign Vector Product.

\Input
  \parm{A} is a list $(a_1,\ldots,_an)$, $n>=0$, of signs.
  \parm{B} is a list $(b_1,\ldots,b_n)$ of signs.

\Output
  \parm{C} is the list $(c_1,\ldots,c_n)$ of the signs 
           such that $c_i=a_i b_i$.
======================================================================*/
#include "qepcad.h"

Word SVPROD(Word A, Word B)
{
       Word Ap,Bp,C,a,b,c;
       /* hide c; */

Step1: /* Compute. */
       Ap = A; Bp = B; C = NIL;
       while (Ap != NIL)
         {
         ADV(Ap,&a,&Ap); ADV(Bp,&b,&Bp);
         c = a * b; C = COMP(c,C);
         }
       C = INV(C);
       goto Return;

Return: /* Prepare for return. */
       return(C);
}
