/*======================================================================
                      t <- MATCHWORD(A,B)

Match word.

\Input
  \parm{A} is a non-null list of characters.
  \parm{B} is a non-null list of characters.

\Ouput
  \parm{t} is 1 if A matches the initial characters of B, 0 otherwise.
======================================================================*/
#include "qepcad.h"

Word MATCHWORD(Word A, Word B)
{
       Word Ap,Bp,t;
       /* hide algorithm */

Step1: /* Check. */
       Ap = A; Bp = B;
       while (FIRST(Ap) == FIRST(Bp))
         {
         Ap = RED(Ap); Bp = RED(Bp);
         if (Ap == NIL) { t = 1; goto Return; }
         if (Bp == NIL) { t = 0; goto Return; }
         }
       t = 0; goto Return;

Return: /* Prepare for return. */
       return(t);
}
