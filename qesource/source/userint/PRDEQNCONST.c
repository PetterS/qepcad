/*===========================================================================
                         PRDEQNCONST()

Process the "d-eqn-const" command.
===========================================================================*/
#include "qepcad.h"

void QepcadCls::PRDEQNCONST()
{
       Word E,E1,E1p,i,j,P,t;

Step1: /* Was propagation of equational constraints requested? */
       if (PCPROPEC == FALSE) {
	 SWRITE("Error PRDEQNCONST: \"prop-eqn-const\" was not issued.\n");
	 goto Return; }

Step2: /* Get the argument. */
       GREADR(&i,&t); if (t == 0) goto Return;

Step3: /* Check for the validity. */
       if (i <= 0 || GVNV < i) {
	 SWRITE("Error PRDEQNCONST: argument must a positive integer <= ");
	 IWRITE(GVNV); SWRITE("\n");
	 goto Return; }

Step4: /* Display the equational constraints at the specified level. */
       E = LELTI(GVEQNCONST,i);
       if (E == NIL) {
	 SWRITE("There are no equational constraints at level ");
	 IWRITE(i); SWRITE(".\n");
	 goto Return; }
       else {
	 P = LELTI(GVPIVOT,i);
	 j = 0;
	 while (E != NIL) {
	   ADV(E,&E1,&E); j++;
	   E1p = E1;
	   SWRITE("E_");IWRITE(i);SWRITE(",");IWRITE(j);SWRITE(" = (");
	   while (E1 != NIL) {
	     LABELWR(FIRST(FIRST(E1)),RED(FIRST(E1)));
	     E1 = RED(E1);
	     if (E1 != NIL) SWRITE(", "); }
	   SWRITE(")");
	   if (P == E1p) SWRITE("  <-- pivot");
	   SWRITE("\n"); } }

Return: /* Prepare for return. */
       return;
}
