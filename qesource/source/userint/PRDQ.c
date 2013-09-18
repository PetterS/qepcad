/*======================================================================
                      PRDQ()

Process "display quantifier list" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDQ()
{
       Word Q,Q_i,V,f,i,r,x_i;
       /* hide f,i,r; */

Step1: /* Process. */
       f = GVNFV; r = GVNV; Q = GVQ; V = GVVL;
       for (i = f + 1; i <= r; i++)
         {
         Q_i = LELTI(Q,i - f); x_i = LELTI(V,i);
         SWRITE("("); QFWR(Q_i); SWRITE(" "); VWRITE(x_i); SWRITE(")");
         }
       SWRITE("\n"); goto Return;

Return: /* Prepare for return. */
       return;
}
