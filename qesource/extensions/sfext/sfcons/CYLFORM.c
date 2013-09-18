/*
C : an ESPCAD
P : the projection factor set for C
k : a level in C
A : a list of atoms from which to construct a formula
 */
#include "qepcad.h"
#include "espcad.h"

Word CYLFORM(Word C, Word P, Word k, Word A)
{
       Word SF,L,Lp,c,S,t,Q,As,Ap,Fp,F,Lt,Lf,s;

Step1: /* Set L to a list of all (k-1)-level cells over which there are
k-level cells with SC_TMPM of TRUE. */
       if (k == 0) {
         SF = LIST1(TRUE);
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

Step3: /* Construct formula for the k-level cells. */
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

Step2: /* Formula for the projection. */
       for(Q = L; Q != NIL; Q = RED(Q))
	 SLELTI(FIRST(Q),SC_TMPM,TRUE);
       As = NIL;
       for(Ap = CINV(A); Ap != NIL; Ap = RED(Ap))
	 if (FMALEVEL(FIRST(Ap)) < k)
	   As = COMP(FIRST(Ap),As);
       Fp = CYLFORM(C,P,k-1,As);

       SF = LIST3(ANDOP,Fp,F);

       
Return: /* Prepare to return. */
       return SF;      
}
