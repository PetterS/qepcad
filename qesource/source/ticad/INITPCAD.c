/*======================================================================
                      D <- INITPCAD()

Initialize Partial CAD.

\Output
  \parm{D) is the partial CAD with the root cell
           whose truth value is set to be \c{UNDET}.
======================================================================*/
#include "qepcad.h"

Word QepcadCls::INITPCAD()
{
       Word D, tv;

Step0: /* Determine truth value! */
       if (GVNA == FALSE || GVNA != NIL && LELTI(GVNA,1) == NEOP && LELTI(GVNA,2) == 0) tv = NA;
       else if (LELTI(GVNQFF,1) == NEOP && LELTI(GVNQFF,2) == 0) tv = FALSE;
       else if (LELTI(GVNQFF,1) == EQOP && LELTI(GVNQFF,2) == 0) tv = TRUE;
       else tv = UNDET;

Step1: /* Make one and initialize it. */
       D = MCELL(0,NIL,FALSE,tv,LIST3(0,LIST2(0,0),NIL),NIL,NIL,0,NIL,NIL);

Return: /* Prepare for return. */
       return(D);
}








