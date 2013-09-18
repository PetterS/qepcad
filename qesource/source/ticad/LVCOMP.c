/*======================================================================
                      t <- LVCOMP(c1,c2)

Level Compare.

\Input
  \parm{c1} is a cell.
  \parm{c2} is another cell.
  
\Output
  \parm{t} is $1$ if the level of $c_1$ is greater than that of $c_2$,
             $-1$ if the level of $c_1$ is less than that of $c_2$,
             $0$  otherwise.
======================================================================*/
#include "qepcad.h"

Word LVCOMP(Word c1, Word c2)
{
       Word h1,h2,t;
       /* hide t; */

Step1: /* Compare. */
       h1 = LELTI(c1,LEVEL); h2 = LELTI(c2,LEVEL);
       t = SIGN(h1 - h2); goto Return;

Return: /* Prepare for return. */
       return(t);
}
