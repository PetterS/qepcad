/*======================================================================
                      GFPCSTAT(c; p1,p0,t1,t0,l)

Gather Final Partial CAD Statistics.

\Input
  \parm{c}  is a cell of the final partial CAD.
  
\Ouput
  \parm{p1} is the number of the propagation solution cells in the
            partial CAD over $c$, including $c$.
  \parm{p0} is the number of the propagation non-solution cells in the
            partial CAD over $c$, including $c$.
  \parm{t1} is the number of the trial evaluation solution cells in the
            partial CAD over $c$, including $c$.
  \parm{t0} is the number of the rial evaluation non-solution cells in the
            partial CAD over $c$, including $c$.
  \parm{l}  is the number of occurrences of the atomic formulas in the
            projection-based formula on the cell $c$.
======================================================================*/
#include "qepcad.h"

void QepcadCls::GFPCSTAT(Word c, Word *p1_, Word *p0_, Word *t1_, Word *t0_, Word *l_)
{
       Word cb,cp,i,j,k,l,lp,p0,p1,pp0,pp1,t0,t1,tp0,tp1,v;
       /* hide j,l,lp,p0,p1,pp0,pp1,t0,t1,tp0,tp1; */

Step1: /* Leaf. */
       p1 = 0; p0 = 0; t1 = 0; t0 = 0; l = 0;
       cb = LELTI(c,CHILD);
       if (cb != NIL) goto Step2;
       i = LELTI(c,HOWTV);
       v = LELTI(c,TRUTH);
       if      (i == BYPRP && v == TRUE)  p1 = 1;
       else if (i == BYPRP && v == FALSE) p0 = 1;
       else if (i == BYTEV && v == TRUE)  t1 = 1;
       else if (i == BYTEV && v == FALSE) t0 = 1;
       else ;
       if (v == TRUE)
         {
         k = LELTI(c,LEVEL);
         for (j = 1; j <= k; j++) l = l + LENGTH(LELTI(GVPF,j));
         }
       goto Return;

Step2: /* Non--leaf. */
       while (cb != NIL)
         {
         ADV(cb,&cp,&cb);
         GFPCSTAT(cp,&pp1,&pp0,&tp1,&tp0,&lp);
         p1 = p1 + pp1;
         p0 = p0 + pp0;
         t1 = t1 + tp1;
         t0 = t0 + tp0;
         l = l + lp;
         }
       goto Return;

Return: /* Prepare for return. */
       *p1_ = p1;
       *p0_ = p0;
       *t1_ = t1;
       *t0_ = t0;
       *l_ = l;
       return;
}
