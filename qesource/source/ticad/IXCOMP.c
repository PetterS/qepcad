/*======================================================================
                      t <- IXCOMP(c1,c2)

Index Compare.

\Input
  \parm{c1} is a cell.
  \parm{c2} is another cell.
  
\Output
  \parm{t} is $1$ if the index of $c_1$ is greater than that of $c_2$ 
                  lexicographically,
             $-1$ if the index of $c_1$ is less than that of $c_2$
                  lexicographically,
             $0$  otherwise.
======================================================================*/
#include "qepcad.h"

Word IXCOMP(Word c1, Word c2)
{
       Word t,x1,x11,x2,x21;
       /* hide t; */

Step1: /* Compare. */
       x1 = LELTI(c1,INDX); x2 = LELTI(c2,INDX);
       while (x1 != NIL && x2 != NIL)
         {
         ADV(x1,&x11,&x1); ADV(x2,&x21,&x2);
         if (x11 > x21) { t = 1; goto Return; }
         if (x11 < x21) { t = -1; goto Return; }
         }
       if (x1 != NIL && x2 == NIL) { t = 1; goto Return; }
       if (x1 == NIL && x2 != NIL) { t = -1; goto Return; }
       t = 0; goto Return;

Return: /* Prepare for return. */
       return(t);
}
