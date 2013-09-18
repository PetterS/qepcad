/*======================================================================
                      PRDFPCSTAT()

Process "Display Final Partial CAD Statistics" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDFPCSTAT()
{
       Word l,p0,p1,t0,t1;
       /* hide l,p0,p1,t0,t1; */

Step1: /* Gather statistics. */
       GFPCSTAT(GVPC,&p1,&p0,&t1,&t0,&l);

Step2: /* Display the statistics. */
       TAB(10); SWRITE("propagation");
       TAB(25); SWRITE("trial-eval");
       TAB(40); SWRITE("total"); SWRITE("\n");
       SWRITE("true");
       TAB(10); FGWRITE(p1,5);
       TAB(25); FGWRITE(t1,5);
       TAB(40); FGWRITE(p1 + t1,5); SWRITE("\n");
       SWRITE("false");
       TAB(10); FGWRITE(p0,5);
       TAB(25); FGWRITE(t0,5);
       TAB(40); FGWRITE(p0 + t0,5); SWRITE("\n");
       SWRITE("total");
       TAB(10); FGWRITE(p1 + p0,5);
       TAB(25); FGWRITE(t1 + t0,5);
       TAB(40); FGWRITE(p1 + p0 + t1 + t0,5); SWRITE("\n\n");
       SWRITE("Length of the projection-based formula :"); GWRITE(l); SWRITE("\n");
       goto Return;

Return: /* Prepare for return. */
       return;
}
