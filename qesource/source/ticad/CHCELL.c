/*======================================================================
                      CHCELL(cs; c,t)

Choose a desired candidate cell.

\Input
  \parm{c*} is a cell.

\Output
  \parm{c} is the next desired candidate cell in the partial CAD on c*.
  \parm{t} is 1 if there is a desired candiate cell, 0 otherwise.
======================================================================*/
#include "qepcad.h"

void QepcadCls::CHCELL(Word cs, Word *c_, Word *t_)
{
       Word c,c1,cb,cp,t,tp,O;
       /* hide t,tp; */

Step1: /* c* is a leaf. */
       cb = LELTI(cs,CHILD);
       if (cb != NIL) goto Step2;
       c = cs; t = 0;
       if ( LELTI(cs,TRUTH) == UNDET && LELTI(cs,LEVEL) < GVNV)
         {
         if (PCUSEDES == 'y') 
           t = ISDESIRED(cs,PCDESIRED);
         else 
           t = 1;
         }
       goto Return;

Step2: /* c is not a leaf. */
       t = 0;
       if ( LELTI(cs, LEVEL) + 1 < GVNFV )
	 O = PCCCSF;
       else
	 O = PCCCS;
       while (cb != NIL)
         {
         ADV(cb,&c1,&cb);
         CHCELL(c1,&cp,&tp);
         if (t == 0)
            {
            if (tp == 1)
               { t = 1; c = cp; }
            }
         else
            {
            if (tp == 1)
              if (CELLCOMP(cp,c,O) < 0)
                 c = cp;
            }
         }

Return: /* Prepare for return. */
       *c_ = c;
       *t_ = t;
       return;
}
