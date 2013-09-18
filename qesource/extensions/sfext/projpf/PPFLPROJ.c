/*======================================================================
                      PPFLPROJ(L,i,P)

Pruned projection factor list project. 

Inputs
  L  : Pruned projection factor list.
  i  : A BETA-digit giving the level which is to be projected to.
  P  : The qepcad list of projection factors.

Side Effects
  The ith componant of the list L is set to the appropriate list of
  projection factors.

======================================================================*/
#include "qepcad.h"

void PPFLPROJ(Word L, Word i, Word P)
{
      Word A,T,p,B,b,t,tp,C;

Step1: /* Loop over each proj. fac. p in level i of P. */
      A = LELTI(P,i);
      T = NIL;
      while(A != NIL) {
	ADV(A,&p,&A);

Step2: /* Decide if p should be in the ith level of the pruned P.F. lsit. */
       /* Get list of historys for p. */
	B = PPF(p);

       /* Loop over each possible history or derivation of p, such is called b. */
	for(t = 0; (B != NIL) && (t == 0); B = RED(B)) {
	  b = FIRST(B);

       /* If this history or derivation is nonempty, check that all pol's
	  in this specific history are already in L.  Then p will be put in L. */
	  if (b != NIL) {
	    for(tp = 1; (b != NIL) && (tp == 1); b = RED(b)) {
	      tp = QPPPFL(FIRST(b),L); }
	    t = tp; } }

Step3: /* If t is true then add p to the ith element of L. */
	if (t) {
	  C = LELTI(L,i);
	  SLELTI(L,i,COMP(p,C)); } }


Return: /* */
      return;

}
