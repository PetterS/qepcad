/*===========================================================================
                         PRCHPIVOT()

Process the "ch-pivot" command.
===========================================================================*/
#include "qepcad.h"

void QepcadCls::PRCHPIVOT()
{
       Word i,j,t,E,P;

Step1: /* Was propagation of equational constraints requested? */
       if (PCPROPEC == FALSE) {
	  SWRITE("Error PRCHPIVOT: \"prop-eqn-const\" was not issued.\n");
	  goto Return; }

Step2: /* Get the argument. */
       GREADR(&i,&t); if (t == 0) goto Return;
       if (CREADB() != ',') {
	  SWRITE("Error PRCHPIVOT: ',' was expected.\n");
	  goto Return; }
       GREADR(&j,&t); if (t == 0) goto Return;

Step3: /* Check for the validity. */
       if (i != GVLV) {
	  SWRITE("You may choose only a ");
	  IWRITE(GVLV); SWRITE("-th level equational constraint.\n");
	  goto Return; }
       
Step4: /* Set the pivot. */
       E = LELTI(GVEQNCONST,i);
       if (E == NIL)
	  SWRITE("Error PRCHPIVOT: There are no constraints at this level.\n");
       else {
	  if (j <= 0 || LENGTH(E) < j)
	     SWRITE("Error PRCHPIVOT: No such equational constraint.\n");
	  else {
	     P = LELTI(E,j);
	     SLELTI(GVPIVOT,i,P); } }

Return: /* Prepare for return. */
       return;
}
