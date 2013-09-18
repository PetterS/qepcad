/*======================================================================
                      I <- GETCID(P,W)

Get a command ID.
    
\Input
  \parm{P} is a list of characters for prompting.
  \parm{W} is a chracter indicating where the interface
           has been called.
           
\Output
  \parm{I} is a $\beta$--integer indicating a command requested
           by the user. (i.e. a command ID)
======================================================================*/
#include "saclib.h"
#include "qepcad.h"

Word GETCID(P,W)
       Word P,W;
{
       Word C,C1,C_i,Cs,I,N,c,m,Csp,k;

Step1: /* Prompt for a command. */
       SWRITE("\n"); PROMPT(); CLOUT(P); 
       if (W == 'b' && GVLV > 1) {
	 SWRITE(" (");
	 CLOUT(LELTI(GVVL,GVLV));
	 SWRITE(")"); }
       SWRITE(" >\n");

Step2: /* Flush the input line. */
       FILINE();

Step3: /* Skip comments. */
       c = CREADB(); BKSP();
       if (c == '[') { COMMNTRD(); goto Step1; }

Step4: /* Get a command name. */
       N = GETWORD();

Step5: /* Match the command. */
       Cs = NIL;
       C = COMMANDS;
       while (C != NIL) {
         ADV(C,&C_i,&C);
         if (MATCHWORD(N,FIRST(C_i))) Cs = COMP(C_i,Cs); }
       Cs = INV(Cs);
       m = LENGTH(Cs);

Step6: /* No matched command. */
       if (m == 0) {
         SWRITE("Error GETCID: There is no such command.\n");
         goto Step1; }

Step7: /* More than one commands matched. */
       if (m > 1) {
	 Csp = Cs;
	 ADV(Csp,&C1,&Csp);
	 k = LENGTH(FIRST(C1));
	 while (Csp != NIL) {
	   if (LENGTH(FIRST(FIRST(Csp))) < k)
	     C1 = FIRST(Csp);
	   Csp = RED(Csp); }

	 if (!EQUAL(N,FIRST(C1))) {
	   SWRITE("Error GETCID: More than one commands are matched.\n");
	   while (Cs != NIL) {
	     ADV(Cs,&C_i,&Cs);
	     SWRITE("              "); CLOUT(FIRST(C_i)); SWRITE("\n"); }
	   goto Step1; } }

Step8: /* Not active here. */
       C1 = FIRST(Cs);
       if (LSRCH(W,THIRD(C1)) == 0) {
         SWRITE("Error GETCID: This command is not active here.\n");
         goto Step1; }

Step9: /* Ok! */
       I = SECOND(C1); goto Return;

Return: /* Prepare for return. */
       return(I);
}
