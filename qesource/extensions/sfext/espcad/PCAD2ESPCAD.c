/*======================================================================
                      PCAD2ESPCAD(P,Ps,Ds,A)

PCAD to ESPCAD conversion.

Inputs
  P  :  A projection factor set structure.
  Ps :  A projection factor set structure, Ps contained in P.
  Ds :  A PCAD cell in the PCAD defined by Ps, where the references
        to QECPAD cell structures are to cells whose signitures
        are defined with respect to Ps.
  A  :  The parent ESPCAD cell for the cell being constructed.

Outputs
  EDs:  An ESPCAD corresponding to the cell Ds.

======================================================================*/
#include "espcad.h"

static Word LIST8(Word a1, Word a2, Word a3, Word a4, Word a5, Word a6, Word a7, Word a8)
{
  return COMP2(a1,a2,LIST6(a3,a4,a5,a6,a7,a8));
}


Word PCAD2ESPCAD(Word P,Word Ps,Word Ds,Word A)
{
       Word C,i,s,ss,P_i,Ps_i,S,Ss,c,EDs,T,t,Tp,u,v;

Step1: /* Initialize. */
       C = LELTI(Ds,SC_REP);
       i = LELTI(C,LEVEL);

Step2: /* Generate correct i-level signiture list. */
       if (i > 0 ) {
         ss = NIL;
         s = FIRST(LELTI(C,SIGNPF));
         P_i = LELTI(P,i); Ps_i = LELTI(Ps,i);
         while(Ps_i != NIL) {
           if (EQUAL(LELTI(FIRST(P_i),PO_LABEL),
                     LELTI(FIRST(Ps_i),PO_LABEL))) {
             ss = COMP(FIRST(s),ss);
             Ps_i = RED(Ps_i); }
           P_i = RED(P_i);
           s = RED(s); }
         s = INV(ss); }

Step3: /* Construct extended Sub-CAD cell structure. */
       EDs = LIST8(C,A,LELTI(Ds,SC_INX),NIL,s,NIL,UNDET,UNDET);

Step4: /* Generate extended child list and add root number vector. */
       S = LELTI(Ds,SC_CDTV);
       if (ISLIST(S)) {
         for(S = CINV(S),Ss = NIL; S != NIL; S = RED(S)) {
           c = FIRST(S);
           Ss = COMP(PCAD2ESPCAD(P,Ps,c,EDs),Ss); }
         S = Ss; }
       else
         SLELTI(EDs,SC_TMPM,S);
       SLELTI(EDs,SC_CDTV,S);
       SLELTI(EDs,SC_RRNV,ESPCADCRNV(EDs));

Step5: /* Set the extended sign vector of cell's children. */
       if (ISLIST(S)) {
	 /* Set T to -1 in all positions corresponding to polynomials
            that vanish identically over EDs, and 1 everywhere else. */
	 for(T = NIL, v = CINV(LELTI(EDs,SC_RRNV)); v != NIL; v = RED(v))
	   if (FIRST(v) == -1)
	     T = COMP(-1,T);
	   else
	     T = COMP(1,T);
	 /* Loop over each child cell, updating T and attatching it. */
	 while (S != NIL) {
	   ADV(S,&s,&S);
	   Tp = CINV(T);
	   u = CINV(LELTI(s,SC_SIGN));
	   for(T = NIL; Tp != NIL; Tp = RED(Tp), u = RED(u)) {
	     t = FIRST(Tp);
	     if (FIRST(u) == 0 || EVEN(t))
	       t++;
	     T = COMP(t,T); }
	   SLELTI(s,SC_EXTS,T); } }

Return: /* Prepare to return. */
       return EDs;

}
