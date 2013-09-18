/*
C : an ESCAD.
P : the projection factor set for C.
k : a level in C.

This function prints out a solution formula based on SC_TMPM mark values. 

 */
#include "extlang.h"
void SC_SLKMF(Word C,Word k);
Word SCFILTER(Word c,Word d);
Word SCCONFLICTQ(Word L1,Word L2);

Word SC_test1(Word C, Word P, Word k)
{
  Word L,Lp,c,t,G,Q,S,Qp,CLt,CLf,Lt,Lf,F,F1;

Step1: /* Set L to a list of all (k-1)-level cells over which there is are
k-level cells with SC_TMPM of TRUE. */
  L = NIL;
  for(Lp = PCADCL(C,k-1); Lp != NIL; Lp = RED(Lp)) {
    c = FIRST(Lp); S = LELTI(c,SC_CDTV); if (!ISLIST(S)) continue;
    for(t = 0; S != NIL && !t; S = RED(S))
      t = (LELTI(FIRST(S),SC_TMPM) == TRUE);
    if (t)
      L = COMP(c,L); }

Step2: /* Set G to a decomposition of L. */
  G = NIL;
  while(L != NIL) {
    
Step3: /* Set Q to the seed for a maximal set of 1-level cells. */
    Q = LIST1(FIRST(L));
    L = RED(L);

Step4: /* Grow Q maximally and add it to G. */
    for(Lp = L, L = NIL; Lp != NIL; Lp = RED(Lp)) {
      c = FIRST(Lp);
      for(t = 1, Qp = Q; Qp != NIL && t; Qp = RED(Qp))
	t = SCFILTER(FIRST(Qp),c);
      if (t)
	Q = COMP(c,Q);
      else
	L = COMP(c,L); }
    G = COMP(Q,G); }

Step5: /* Print out formulas. */
  F = NIL;
  for(t = 0 ; G != NIL; G = RED(G)) {

Step6: /* Construct formula for cells over the base. */
    for(CLt = NIL, CLf = NIL, L = FIRST(G); L != NIL; L = RED(L)) {
      LTFOCWTVMARK(FIRST(L),&Lt,&Lf);
      CLt = CCONC(Lt,CLt);
      CLf = CCONC(Lf,CLf); }
    F1 = FDBTACL(CLt,CLf,P,LIST2(NIL,NIL),k);

Step7: /* Construct a formula for the base. */
    if (k > 1) {
      ESCSLKMF(C,k - 1);
      for(L = FIRST(G); L != NIL; L = RED(L))
	SLELTI(FIRST(L),SC_TMPM,TRUE);
      F1 = LIST3(ANDOP,SC_test(C,P,k-1),F1); }
    F = COMP(F1,F); }

Step8: /* Put results together. */
  if (LENGTH(F) > 1)
    F = COMP(OROP,F);
  else
    F = FIRST(F);

Return: /* Prepare to return. */
   return F;
}



