/*
C : an ESPCAD
P : the projection factor set for C
k : a level in C
A : a list of atoms from which to construct a formula
 */
#include "qepcad.h"
#include "espcad.h"

Word CYLIMPFORM(Word C, Word P, Word k, Word A)
{
       Word SF,L,Lp,c,S,t,Q,As,Ap,Fp,F,Lt,Lf,s,Si,Fi,Qp,SF2;

Step1: /* Set L to a list of all (k-1)-level cells over which there are
k-level cells with SC_TMPM of TRUE. */
       if (k == 0) {
	 if (LELTI(C,SC_TMPM) == TRUE)
	   SF = LIST1(TRUE);
	 else 
	   SF = LIST1(FALSE);
         goto Return; }
       SF = NIL;
       L = NIL;
       for(Lp = PCADCL(C,k-1); Lp != NIL; Lp = RED(Lp)) {
         c = FIRST(Lp); 
	 S = LELTI(c,SC_CDTV); if (!ISLIST(S)) continue;
         for(t = 0; S != NIL && !t; S = RED(S))
           t = (LELTI(FIRST(S),SC_TMPM) == TRUE);
         if (t)
           L = COMP(c,L); }

Step2: /* Construct formula for the k-level cells. */
       Lt = NIL;
       Lf = NIL;
       S = NIL;
       for(Lp = L; Lp != NIL; Lp = RED(Lp))
	 S = CCONC(LELTI(FIRST(Lp),SC_CDTV),S);
       for(S = PCADCL(C,k); S != NIL; S = RED(S)) {
	 s = FIRST(S);
	 if (LELTI(s,SC_TMPM) == TRUE)
	   Lt = COMP(s,Lt);
	 else
	   Lf = COMP(s,Lf); }
       F = NAIVESF(SPCADCBDD(Lt,k),Lf,A,P);

Step3: /* */
       S = GEOPARTII(FMASORT(FMA2DNF(F)),L,P,NIL);
       /* Construct definiting formula from each (Si,Fi) in S. */
       for(; S != NIL; S = RED(S)) {
	 FIRST2(FIRST(S),&Si,&Fi);
	 ESCSLKMF(C,k-1);
	 for(Qp = Si; Qp != NIL; Qp = RED(Qp))
	   SLELTI(FIRST(Qp),SC_TMPM,TRUE);
	 SF2 = CYLIMPFORM(C,P,k-1,A);
	 SF = COMP(LIST3(ANDOP,SF2,CLEANUPFORM(Si,Fi,P)),SF); }

 Step4: /* Convert SF from a list of formulas to a formula. */
       if (LENGTH(SF) > 1)
	 SF = COMP(OROP,SF);
       else
	 SF = FIRST(SF);
       
Return: /* Prepare to return. */
       return SF;      
}

/*
Inputs
S:  a set of cells of level k - 1.
F:  a DNF formula (formally speaking!)
P:  the projection factors that go with the cells in S.
Outputs
Fp: a formula that, restricted to the children of S, is
    equivalent to F.
*/
Word CLEANUPFORM(Word S,Word F,Word P)
{
    Word Sp,L,Fp;
    for(Sp = S, L = NIL; Sp != NIL; Sp = RED(Sp))
      L = CCONC(LELTI(FIRST(Sp),SC_CDTV),L);
    Fp = CF(L,F,P);
    return Fp;
}

Word UNIFORMTV(Word L,Word F,Word P)
{
  Word t,f,u,Lp,x;
  t = 0; f = 0; u = 0;
  for(Lp = L; Lp != NIL; Lp = RED(Lp)) {
    x = FMACELLEVAL(F,FIRST(Lp),P);
    if (x == TRUE) t++;
    else if (x == FALSE) f++;
    else if (x == UNDET) u++; }
  if (t && !f && !u) return TRUE;
  if (!t && f && !u) return FALSE;
  return UNDET;
}

Word CF(Word L,Word F,Word P)
{
  Word Fp,A,Ap,f;

  switch(FIRST(F)) {
  case (TRUE)  : Fp = F; break;
  case (FALSE) : Fp = F; break;
  case (ANDOP) : 
    A = RED(F);
    for(Ap = NIL; A != NIL; A = RED(A)) {
      f = CF(L,FIRST(A),P);
      if (FIRST(f) == FALSE) {
	Fp = f;
	goto Return; }
      if (FIRST(f) != TRUE)
	Ap = COMP(f,Ap); }
    if (Ap == NIL)
      Fp = LIST1(TRUE);
    else if (LENGTH(Ap) == 1)
      Fp = FIRST(Ap);
    else
      Fp = COMP(ANDOP,Ap);
    break;
  case (OROP) :
    A = RED(F);
    for(Ap = NIL; A != NIL; A = RED(A)) {
      f = CF(L,FIRST(A),P);
      if (FIRST(f) == TRUE) {
	Fp = f;
	goto Return; }
      if (FIRST(f) != FALSE)
	Ap = COMP(f,Ap); }
    if (Ap == NIL)
      Fp = LIST1(FALSE);
    else if (LENGTH(Ap) == 1)
      Fp = FIRST(Ap);
    else
      Fp = COMP(OROP,Ap);
    break;
  default:
    f = UNIFORMTV(L,F,P);
    if (f == UNDET)
      Fp = F;
    else
      Fp = LIST1(f);
    break; }
Return:
  return Fp;
}
