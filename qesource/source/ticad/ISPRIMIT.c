/*======================================================================
                      t <- ISPRIMIT(s)

Is it a primitive sample point?

\Input
  \parm{s} is a sample point.

\Output
  \parm{t} is 1 if \v{s} is a primitive sample point, 0 otherwise.
======================================================================*/
#include "qepcad.h"

Word ISPRIMIT(Word s)
{
       Word t;
       /* hide t; */

Step1: /* Check. */
       if (LENGTH(s) == 5) t = 0; else t = 1; goto Return;

Return: /* Prepare for return. */
       return(t);
}
