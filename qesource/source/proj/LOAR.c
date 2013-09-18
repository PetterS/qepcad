/*===========================================================================
                           R <- LOAR(k,Q,F)

List of Ancestral Resultants.

Inputs
   k:  a beta-integer, k >= 2.
   Q:  the list of projection polynomials in k - 1 variables.
   F:  an irreducible factor of some of the polynomials in Q.

Output
   R:  a list of all the descriptions of resultants of level k
       projection factors of which F is a factor.
===========================================================================*/
#include "qepcad.h"

Word LOAR(Word k, Word Q, Word F)
{
       Word I,J,L,P,P1,Ph,Ph1,Php,Pp,Q1,R;

Step1: /*  */
       R = NIL;
       P = LELTI(F,PO_PARENT);
       Pp = P;
       while (Pp != NIL) {
	  ADV(Pp,&P1,&Pp);
	  P1 = LELTI(P1,PO_PARENT);
	  L = LELTI(P1,PO_LABEL);
	  I = LBLLEVEL(L);
	  if (I < k) {
	     J = LBLINDEX(L);

	     /* Q1 = LELTI(Q,J); */
	     for(Q1 = Q; LBLINDEX(LELTI(FIRST(Q1),PO_LABEL)) != J; 
		 Q1 = RED(Q1));
	     Q1 = FIRST(Q1);
	     
	     Ph = LELTI(Q1,PO_PARENT);
	     Php = Ph;
	     while (Php != NIL) { 
		ADV(Php,&Ph1,&Php);
		if (FIRST(Ph1) == PO_RES) R = COMP(Ph1,R); } } }
       
Return: /* Prepare for return. */
       return (R);
}
