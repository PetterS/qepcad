/*======================================================================
                      CELLFIDX(x,c; cp,t)

Cell From Index.

\Input
  \pamr{x} is the index of a cell over the cell $c$.
  \parm{c} is a cell.

\Output
  \parm{c'} is the cell above the cell $c$ corresponding to the index $x$.
  \parm{t} is 1 if successful 0 otherwise.
======================================================================*/
#include "qepcad.h"

void CELLFIDX(Word x, Word c, Word *cp_, Word *t_)
{
       Word c1,cb,cp,t,x1,xp,y,y1;
       /* hide t; */

Step1: /* $x = ()$. */
       if (x == NIL) { cp = c; t = 1; goto Return; }

Step2: /* Set up. */
       cb = LELTI(c,CHILD);

Step3: /* $c $is a leaf. */
       if (cb == NIL) { t = 0; goto Return; }

Step4: /* $c$ is not a leaf. */
       ADV(x,&x1,&xp);
       while (cb != NIL)
         {
         ADV(cb,&c1,&cb);
         y = LELTI(c1,INDX);
         y1 = FIRST(LASTCELL(y));
         if (y1 == x1) { CELLFIDX(xp,c1,&cp,&t); goto Return; }
         }
       t = 0; goto Return;

Return: /* Prepare for return. */
       *cp_ = cp;
       *t_ = t;
       return;
}
