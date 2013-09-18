/* Sub-CAD to Extended-Sub-CAD. */
#include "extlang.h"

static Word LIST7(Word a1, Word a2, Word a3, Word a4, Word a5, Word a6, Word a7)
{
  return COMP(a1,LIST6(a2,a3,a4,a5,a6,a7));
}

Word SCAD2ESCAD(Word P, Word Ps, Word Ds, Word A)
{
       Word C,i,s,ss,P_i,Ps_i,S,Ss,c,EDs;

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
       EDs = LIST7(C,A,LELTI(Ds,SC_INX),NIL,s,NIL,UNDET);

Step4: /* Generate extended child list. */
       S = LELTI(Ds,SC_CDTV);
       if (ISLIST(S)) {
	 for(S = CINV(S),Ss = NIL; S != NIL; S = RED(S)) {
	   c = FIRST(S);
	   Ss = COMP(SCAD2ESCAD(P,Ps,c,EDs),Ss); }
	 S = Ss; }
       else
	 SLELTI(EDs,SC_TMPM,S);

       SLELTI(EDs,SC_CDTV,S);

Return: /* Prepare to return. */
       return EDs;

}
