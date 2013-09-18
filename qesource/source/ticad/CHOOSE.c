/*======================================================================
                      CHOOSE(D; t,c)

Choose a cell.

\Input
  \parm{D} is a partial CAD.

\Output
  \parm{t} is 1 if there is a desired candidate cell, 0 otherwise. 
  \parm{c} is a desired candidate cell chosen.
======================================================================*/
#include "qepcad.h"

void QepcadCls::CHOOSE(Word D, Word *t_, Word *c_)
{
       Word c,t;
       /* hide t; */

Step1: /* Manually chosen? */
       if (PCMC == 'y') 
       { 
	 c = PCMCC; 
	 PCMC = 'n'; 
	 t = 1; 
	 GVECPI = 0; /* Forces a new search for cells in need of stacks. */
	 goto Return; }

Step2: /* Choose. */
       if (PCCHFLAG)
	   ECLI(D,&c,&t);
       else
	 CHCELL(D,&c,&t);

Return: /* Prepare for return. */
       *t_ = t;
       *c_ = c;
       return;
}
