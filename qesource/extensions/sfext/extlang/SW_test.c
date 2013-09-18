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

Word SC_test(Word C, Word P, Word k)
{
  Word L,Lp,c,t,G,Q,S,Qp,CLt,CLf,Lt,Lf,F,F1,FP,PL,LBC1,LBC2;
  Word Fp,n,f1,f2,LBC,t1,t2,either,e;

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
    F1 = FMA_CONSTRUCT(CLt,CLf,P,k);
    /*    F1 = FDBTACL(CLt,CLf,P,LIST2(NIL,NIL),k,1);*/

StepX: /* See if the set FIRST(G) ought to be split further. */
    Fp = FMA2DNF(F1);
    PL = RED(Fp);
    n = LENGTH(PL);
    if (n == 1) goto Step7;
    /*  We're gonna try all partitionings of the products into two pieces
	and see if any of them yield a partition of the base cells. */
    for(Lp = PARTLIST(n); Lp != NIL; Lp = RED(Lp)) {
      FIRST2(SPLITBYPART(PL,FIRST(Lp),n),&f1,&f2);
      f1 = COMP(OROP,f1); f2 = COMP(OROP,f2);
      
      LBC1 = NIL; LBC2 = NIL; either = NIL;
      for(LBC = FIRST(G); LBC != NIL; LBC = RED(LBC)) {
	t1 = FMADMQ(f1,LIST1(FIRST(LBC)),1,P);
	t2 = FMADMQ(f2,LIST1(FIRST(LBC)),1,P);
	if (!t1 && !t2)
	  break;
	if (t1 && t2)
	  either = COMP(FIRST(LBC),either); 
	else if (t1)
	  LBC1 = COMP(FIRST(LBC),LBC1);
	else if (t2)
	  LBC2 = COMP(FIRST(LBC),LBC2); }

      if (!t1 && !t2)
	continue;
      while (either != NIL) {
	ADV(either,&e,&either);
	if (ISCLOSEST2(e,LBC1,LBC2) == 1)
	  LBC1 = COMP(e,LBC1);
	else
	  LBC2 = COMP(e,LBC2); }
      G = COMP2(LBC1,LBC2,RED(G));
      goto Step6; }


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
