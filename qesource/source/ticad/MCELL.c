/*======================================================================
                      c <- MCELL(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10)

Make a Cell

\Input
  \parm{a1} is the level.
  \parm{a2} is the list of children cells.
  \parm{a3} is the assignment flag. (Reserved for parallel algorithm)
  \parm{a4} is the truth value.
  \parm{a5} is the sample point.
  \parm{a6} is the index.
  \parm{a7} is the projection factor signature.
  \parm{a8} is the indicator
  \parm{a9} is the degrees of the substituted projection factors
  \parm{a10} is the multiplicies.

\Output
  \parm{c} is a new cell.
======================================================================*/
#include "qepcad.h"

Word MCELL(Word a1, Word a2, Word a3, Word a4, Word a5, Word a6, Word a7, Word a8, Word a9, Word a10)
{
       Word c;

Step1: /* Make it. */
       c = NIL;
       c = COMP(a10,c);
       c = COMP(a9,c);
       c = COMP(a8,c);
       c = COMP(a7,c);
       c = COMP(a6,c);
       c = COMP(a5,c);
       c = COMP(a4,c);
       c = COMP(a3,c);
       c = COMP(a2,c);
       c = COMP(a1,c);
       goto Return;

Return: /* Prepare for return. */
       return(c);
}


