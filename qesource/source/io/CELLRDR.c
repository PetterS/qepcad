/*======================================================================
                      CELLRDR(D; c,t)

Cell Read, Robust.

\Input
  \parm{D} is a partial CAD.
  
\Output
  \parm{c} is a cell in $D$ whose index has been read from the input stream.
  \parm{t} is 1 if successful, 0 otherwise.
======================================================================*/
#include "qepcad.h"

void CELLRDR(Word D, Word *c_, Word *t_)
{
       Word c,t,x;
       /* hide t; */

Step1: /* Read in a cell index. */
       XREADR(&x,&t); if (t == 0) goto Return;

Step2: /* Get a cell from the index. */
       CELLFIDX(x,D,&c,&t);
       if (t == 0) { LWRITE(x); SWRITE(" is not an existing cell.\n"); }

Return: /* Prepare for return. */
       *c_ = c;
       *t_ = t;
       return;
}
