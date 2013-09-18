/*======================================================================
                      t <- ISATOMF(F)

Is Atomic Formula?

\Input
  \parm{F} is a quantifier--free formula.
  
\Output
  \parm{t} is 1 if \v{F} is an atomic formula, 0 otherwise.
======================================================================*/
#include "qepcad.h"

Word ISATOMF(Word F)
{
       Word T,t;
       /* hide t; */

Step1: /* Check. */
       T = FIRST(F);
       if (T == LTOP || T == EQOP || T == GTOP || T == GEOP || T == NEOP || T == LEOP || T == IROOT)
         t = 1;
       else
         t = 0;
       goto Return;

Return: /* Prepare for return. */
       return(t);
}
