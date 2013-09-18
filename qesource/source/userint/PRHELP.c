/*======================================================================
                      PRHELP(W)

Process "help" command.

\Input
  \parm{W} is a character indicating where this 
           has been called.
======================================================================*/
#include "qepcad.h"

void PRHELP(Word W)
{
       Word C,C1,D,D1,E,F,F1,i,j,n,rows1,rows2;

Step1: /* Initialize. */
       D = COMCLASS;

Step2: /* List the commands by classification. */
       if (D == NIL) goto Step5;
       ADV(D,&D1,&D);
       SWRITE("-------------------------------------");
       SWRITE("--------------------------------------\n");
       CLOUT(SECOND(D1));SWRITE("\n");

Step3: /* Get commands in this classification. */
       C = COMMANDS;
       E = NIL;
       while (C != NIL) {
	  ADV(C,&C1,&C);
	  if (EQUAL(FOURTH(C1),FIRST(D1)))
	     E = COMP(C1,E); }
       E = INV(E);

Step4: /* Print column-wise. */
       n = LENGTH(E);
       rows1 = RNCEIL(RNQ(RNINT(n),RNINT(3)));
       if (MDHOM(3,n) == 1)
	  rows2 = rows1 - 1;
       else
	  rows2 = rows1;

       for (i = 1; i <= rows1; i++) {
	  F = E; j = 0;

	  while (F != NIL && j < i) {
	     ADV(F,&F1,&F); j++; }
	  if (j == i) {
	     CLOUT(FIRST(F1));
	     if (LSRCH(W,THIRD(F1)) == 0) SWRITE("*"); }

	  while (F != NIL && j < i+rows1) {
	     ADV(F,&F1,&F); j++; }
	  if (j == i+rows1 && (i < rows1 || rows1 == rows2)) {
	     TAB(25);
	     CLOUT(FIRST(F1));
	     if (LSRCH(W,THIRD(F1)) == 0) SWRITE("*"); }

	  while (F != NIL && j < i+rows1+rows2) {
	     ADV(F,&F1,&F); j++; }
	  if (j == i+rows1+rows2) {
	     TAB(50);
	     CLOUT(FIRST(F1));
	     if (LSRCH(W,THIRD(F1)) == 0) SWRITE("*"); }
	  
	  SWRITE("\n"); }
       
       goto Step2;

Step5: /* Write final comments. */
       SWRITE("-------------------------------------");
       SWRITE("--------------------------------------\n");
       SWRITE("*) inactive commands\n\n");
       SWRITE("For more information on command xxxx, type \"whatis xxxx\".\n");

Return: /* Prepare for return. */
       return;
}
