/*======================================================================
                      PRPROPEC()

Process prop-eqn-const command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRPROPEC()
{
       Word C,i,r;

Step1: /* Toggle the PCPROPEC global variable and initialize globals. */
       GVEQNCONST = GVPIVOT = NIL;
       GVEQN2A = NIL;

       if (PCPROPEC == FALSE) {
	 PCPROPEC = TRUE;
	 r = LENGTH(GVVL);
	 for (i = 1; i <= r; i++) {
	   GVEQNCONST = COMP(NIL,GVEQNCONST);
	   GVPIVOT = COMP(NIL,GVPIVOT); } }

       else
	 PCPROPEC = FALSE;

Return: /* Prepare for return. */
       return;
}
