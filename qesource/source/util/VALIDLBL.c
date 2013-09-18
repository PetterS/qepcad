/*===========================================================================
                         t <- VALIDLBL(L)

Valid label?

Inputs
  L : a triple (C,i,j), where C is a list of characters and i and j are 
      BETA-digits.
  P : the projection factor set to which the label is supposed to refer!

Output
  t : If L is the label of some polynomial in GVPF then t = TRUE,
      otherwise t = FALSE.
===========================================================================*/
#include "qepcad.h"

Word VALIDLBL(Word L, Word P)
{
       Word t,P1,A;

Step1: /* Initialize. */
       t = FALSE;

Step2: /* Loop. */
       while (P != NIL) {
	 ADV(P,&P1,&P);
	 while (P1 != NIL) {
	   ADV(P1,&A,&P1);
	   if (EQUAL(LELTI(A,PO_LABEL),L)) {
	     t = TRUE;
	     goto Return; } } }

Return: /* Prepare for return. */
       return(t);
}
