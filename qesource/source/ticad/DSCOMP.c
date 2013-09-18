/*======================================================================
                      t <- DSCOMP(c1,c2)

Degree of Sample point Compare.

\Input
  \parm{c1} is a non-root cell.
  \parm{c2} is another non-root cell.
  
\Output
  \parm{t} is $1$ if the presumed degree of the primitive sample point of
                  $c_1$ is greather than that of $c_2$,
             $-1$ if the presumed degree of the primitive sample point of
                  $c_1$ is less than that of $c_2$, and
             $0$  otherwise.
======================================================================*/
#include "qepcad.h"

Word DSCOMP(Word c1, Word c2)
{
       Word d1,d2,t;
       /* hide d1,d2,t; */

Step1: /* Compare. */
       d1 = CELLDEG(c1);
       d2 = CELLDEG(c2);
       t = SIGN(d1 - d2);

Return: /* Prepare for return. */
       return(t);
}
