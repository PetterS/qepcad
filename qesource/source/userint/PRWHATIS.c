/*===========================================================================
                              PRWHATIS()

Process "whatis" commnad.
===========================================================================*/
#include "qepcad.h"

void PRWHATIS()
{
       Word C,C1,C_i,Cs,Csp,I,k,N,m;

Step1: /* Read in a command name. */
       N = GETWORD();

Step2: /* Match the command. */
       Cs = NIL;
       C = COMMANDS;
       while (C != NIL) {
	  ADV(C,&C_i,&C);
	  if (MATCHWORD(N,FIRST(C_i))) Cs = COMP(C_i,Cs); }
       Cs = INV(Cs);
       m = LENGTH(Cs);

Step3: /* No matched command. */
       if (m == 0) {
	  SWRITE("Error WHATIS: There is no such command!\n");
	  goto Return; }

Step4: /* More than one command matched. */
       if (m > 1) {
	  Csp = Cs;
	  ADV(Csp,&C1,&Csp);
	  k = LENGTH(FIRST(C1));
	  while (Csp != NIL) {
	     if (LENGTH(FIRST(FIRST(Csp))) < k)
		C1 = FIRST(Csp);
	     Csp = RED(Csp); }

	  if (!EQUAL(N,FIRST(C1))) {
	     SWRITE("Error WHATIS: More than one command is matched.\n");
	     while (Cs != NIL) {
		ADV(Cs,&C_i,&Cs);
		SWRITE("              "); CLOUT(FIRST(C_i)); SWRITE("\n"); }
	     goto Return; } }

Step5: /* Give help on the command. */
       C1 = FIRST(Cs); I = SECOND(C1);
       HELPWR(I);
       goto Return;

Return: /* Prepare for return. */
       return;
}
