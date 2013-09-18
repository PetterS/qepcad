/*======================================================================
                      t <- SSCOMP(c1,c2)

Sector/Section  Compare.

\Input
  \parm{c1} is a non-root cell.
  \parm{c2} is another non-root cell.
  
\Output
  \parm{t} is $1$ if $c_1$ is a section and $c_2$ is a sector,
             $-1$ if $c_1$ is a sector and $c_2$ is a section,
             $0$  otherwise.
======================================================================*/
#include "qepcad.h"

Word SSCOMP(Word c1, Word c2)
{
       Word t,x1,x2;
       /* hide t,x1,x2; */

Step1: /* Compare. */
       x1 = EVEN(FIRST(LASTCELL(LELTI(c1,INDX))));
       x2 = EVEN(FIRST(LASTCELL(LELTI(c2,INDX))));
       t = x1 - x2;
       goto Return;

Return: /* Prepare for return. */
       return(t);
}
