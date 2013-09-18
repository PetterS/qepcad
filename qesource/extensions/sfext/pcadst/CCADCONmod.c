/*======================================================================
                      CCADCONmod(n,P,C;Ps,Cs)

Coarse CAD construction (modified).  In some special cases (e.g. when
it is known that the solution space can be expressed as the closure
of an open set) we can simplify a CAD without looking at truth values
for any section cells.  This version of CCADCON works this way.

Inputs
  n  : The dimension of the CAD.
  P  : The qepcad data structure for the projection factors.
  C  : The partial CAD.

Outputs
  Ps : The qepcad data structure for projection factors, for the 
       pruned projection factors.
  Cs : The pruned partial CAD.

======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

void CCADCONmod(Word n, Word P, Word C, Word *Ps_, Word *Cs_)
{
      Word Ps,i,Cs,Q,S,c,L,Lp,b,d,bs,ds,cs,T1,T2;

Step1: /* Set Ps to the empty projection list, and Cs to the full 
original CAD C. */
      Ps = NIL; for(i = 0; i < n; i++) { Ps = COMP(NIL,Ps); }
      Cs = SCADDSCON(C,NIL,n);

Step2: /* Loop over each level i from n down to 1. */
      for(i = n; i > 0; i--) {
	Q = NIL;

Step3: /* Projection of Ps_{i+1}, ... , Ps_{n} onto level i. */
        if (i < n)
	  PPFLPROJ(Ps,i,P);

Step4: /* Loop over each level i section cell c. */
	for(S = CADSCL(C,i); S != NIL; S = RED(S)) {
	  c = FIRST(S);

Step5: /* Set L to a list of all level i projection factors of which 
c is a section, then determine if c is a section of any polynomial 
already in Ps. */
	  L = LPFZC(c,P);
	  for(Lp = L; (Lp != NIL) && (QPPPFL(FIRST(Lp),Ps) != 1); 
	      Lp = RED(Lp));
	  if (Lp == NIL) {

Step6: /* Determine if cell c and its stack nieghbors have the same 
truth structure. If not, add L to Q.  L represents a condition on 
the set of proj. pols. */
	    CSN(c,C,&b,&d); 
	    bs = PCADCFCADC(b,Cs); 
	    ds = PCADCFCADC(d,Cs);
	    if (( ! CTSEQ(bs,ds))) {
	      Q = COMP(L,Q); } } }

Step7: /* Find a minimum hitting set for Q. */
	T1 = PPFMINHITSET(Q,P,i);

Step8: /* End of loop.  Set level i pruned proj fac's. Build ith 
level of Cs. */
	T2 = PFSUNION(T1,LELTI(Ps,i));
	SLELTI(Ps,i,T2);
	PLCAD(Cs,i,Ps,P); }

Return:
      *Cs_ = Cs;
      *Ps_ = PFSREORDERREV(P,Ps);
}
