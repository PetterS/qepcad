/*======================================================================
                      A <- MPOLY(a1,a2,a3,a4,a5)

Make a polynomial structure.

\Input
  \parm{a1} is the polynomial.
  \parm{a2} is the label.
  \parm{a3} is the parentages.
  \parm{a4} is the type.
  \parm{a5} is the status.

\Output
  \parm{c} is a new polynomial structure.
======================================================================*/
#include "qepcad.h"

Word MPOLY(Word a1, Word a2, Word a3, Word a4, Word a5)
{
       Word A;

Step1: /* Make it. */
       A = NIL;
       A = COMP(a5,A);
       A = COMP(a4,A);
       A = COMP(a3,A);
       A = COMP(a2,A);
       A = COMP(a1,A);

Return: /* Prepare for return. */
       return(A);
}

