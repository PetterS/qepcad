/*======================================================================
                        cp <- DESCENDANT(c,x,kp)

Descendant.

\Input
  \parm{c}  is a cell.
  \parm{x}  is an index of a descendant of the cell c.
  \parm{k'} is a level.

\Output
  \parm{c'} is the level $k'$ descendant of $c$ whose index is
            a first sublist of $x$.
            In case $k'$ is less than the level of $c$, 
            $c'$ is set to $c$.
======================================================================*/
#include "qepcad.h"

Word DESCENDANT(Word c, Word x, Word kp)
{
       Word k,cp,xi,cb,i;

Step1: /* Trivial case. */
       k = LELTI(c,LEVEL);
       if (kp <= k)
         {
         cp = c;
         goto Return;
         }

Step2: /* General case. */
       for (i=1; i<=k; i++)
         x = RED(x);
       cp = c;
       for (i=k+1; i<=kp; i++)
         {
         ADV(x,&xi,&x);
         cb = LELTI(cp,CHILD);
         cp = LELTI(cb,xi);
         }

Return: /* Prepare for return. */
       return(cp); 
}


