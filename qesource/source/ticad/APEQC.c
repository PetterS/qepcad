/*======================================================================
                      APEQC(c,k,P)

Apply equational constraints.

Inputs
   c : a cell over which a stack has just been constructed.
   k : the level of c.
   P : the list of projection factors.

Output
   None.

Effect
   If there are no (k+1)-level constraints nothing is done.
   Otherwise each cell of the stack over c which fails to satisfy 
   each k-level constraint has its truth value set to FALSE and its 
   HOWTV field set to BYEQC.
======================================================================*/
#include "qepcad.h"

void QepcadCls::APEQC(Word c, Word k, Word P)
{
        Word c1,E,E1,E11,Ep,Ep1,h,i,j,m,M,Mp,S,t,tp,Ps,p;

Step1: /* Get (k+1)-level equational constraints, if none, return. */
	E = LELTI(GVEQNCONST,k+1);
	if (E == NIL) return;

Step2: /* Get the stack over c. */
	S = LELTI(c,CHILD);

Step3: /* Get the next cell in stack with undetermined truth value. */
	if (S != NIL)
	   ADV(S,&c1,&S);
	else
	   goto Return;
	t = LELTI(c1,TRUTH);
	if (t != UNDET)
	   goto Step3;

Step4: /* Get the signature list of the cell. */
	M = LELTI(c1,SIGNPF);

Step5: /* Initialize the constraint list. */
	Ep = E;

Step6: /* Get the next constraint, if any, and initialize it;*/
       /* else return. */
	if (Ep == NIL)
	  goto Step3;
	else {
	  ADV(Ep,&E1,&Ep);
	  Ep1 = E1; }
	
Step7: /* Get the level and index of the next element of the constraint, 
if any; else set truth value of cell to FALSE and return for next cell. */
	if (Ep1 == NIL) {
	  SLELTI(c1,TRUTH,FALSE);
	  SLELTI(c1,HOWTV,BYEQC);
	  if (k < GVNFV) GVEQN2A = SUNION(GVEQN2A,LIST1(E));
	  goto Step3; }
	else {
	  ADV(Ep1,&E11,&Ep1);
	  i = SECOND(E11);
	  j = THIRD(E11); }

Step8: /* Check whether P_i,j is zero in c1. */
	Mp = LELTI(M,k + 2 - i);
	Ps = LELTI(P,i);
	while (Mp != NIL) {
	  ADV(Mp,&m,&Mp);
	  ADV(Ps,&p,&Ps);
	  if (m == 0 && THIRD(LELTI(p,PO_LABEL)) == j)
	    goto Step6; }
	goto Step7;
	
Return: /* Prepare for return. */
        return;
}
