/*======================================================================
                      PLCAD(Cs,i,Ps,P)

Prune level of CAD.

Inputs
  Cs : A pruned partial CAD data structure.
  i  : A level.
  Ps : A pruned Projection factor list.
  P  : The original projection factor list.

Side Effects
  Level i of Cs is pruned according to Ps.

======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

void PLCAD(Word Cs, Word i, Word Ps, Word P)
{
      Word L,A,S,Sp,Ss,s,Q,t,k,cs;

Step1: /* Loop over each i-1 cell. */
      for(L = PCADCL(Cs,i-1); L != NIL; L = RED(L)) {
	A = FIRST(L);

Step2: /* Loop over the stack S of A.  If a section cell is found to
	  be a section of no pol in LELTI(Ps,i). */
	S = LELTI(A,SC_CDTV);
	if (ISLIST(S)) {
	Sp = LIST1(FIRST(S));
	for(S = RED(S); S != NIL; S = RED(S)) {
	  ADV(S,&s,&S);
	  //	  Q = LPFZC(LELTI(s,SC_REP),P);
	  Q = LPFOWCS(LELTI(s,SC_REP),LELTI(FIRST(S),SC_REP),P);
	  for(t = 0; (Q != NIL) && (t == 0); Q = RED(Q))
	    t = QPPPFL(FIRST(Q),Ps);
	  if (t) {
	    Sp = COMP2(FIRST(S),s,Sp); } }

Step3: /* Reverse the order of Sp, and reindex the cells. */
	Ss = NIL;
	for(k = LENGTH(Sp); Sp != NIL; k--) {
	  ADV(Sp,&cs,&Sp);
	  SLELTI(cs,SC_INX,k);
	  Ss = COMP(cs,Ss); }

Step4: /* Set the children list of A to the new stack. */
	SLELTI(A,SC_CDTV,Ss); } }

Return: /* */
      return;
}
