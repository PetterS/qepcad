/*======================================================================
                      t <- TYPEQFF(F)

Type of Quantifier Free Formula.

\Input
  \parm{F} is a quantifier--free formula.

\Output
  \parm{t} is \c{TRUE}  if \v{F} is a true  constant atomic formula,
              \c{FALSE} if \v{F} is a false constant atomic formula,
              \c{UNDET} otherwise.
======================================================================*/
#include "qepcad.h"

Word TYPEQFF(Word F)
{
       Word t;
       /* hide t; */

Step1: /* Check. */
       if (!ISATOMF(F)) { t = UNDET; goto Return; }
       t = TYPEAF(F); goto Return;

Return: /* Prepare for return. */
       return(t);
}
