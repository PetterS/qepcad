/*======================================================================
                      CCADCONEXT(n,P,C;Ps,Cs)

Coarse CAD construction - extended.

Inputs
  n  : The dimension of the CAD.
  P  : The qepcad data structure for the projection factors.
  C  : The partial CAD.

Outputs
  Ps : The qepcad data structure for projection factors, for the 
       pruned projection factors.
  Cs : The pruned partial CAD.
  N  : A list (L_1, ..., L_n), where L_i is a list of the polynomials
       which were chosen in Step 7.

======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

void CCADCONEXT(Word n, Word P, Word C, Word *Ps_, Word *Cs_, Word *N_)
{
      Word Ps,i,Cs,Q,S,c,L,Lp,b,d,bs,ds,cs,T1,T2,N,Np;

Word t;

Step1: /* Initialization: Set Ps to a list of n empty lists. */
      N = NIL;
      Ps = NIL; for(i = 0; i < n; i++) { Ps = COMP(NIL,Ps); }

t = ACLOCK();
      Cs = SCADDSCON(C,NIL,n);
t = ACLOCK() - t;
//if (PCVERBOSE) { SWRITE("--SCADDSCON  : "); IWRITE(t); SWRITE("\n"); }

Step2: /* Loop over each i from n down to 1. */
      for(i = n; i > 0; i--) {
	Q = NIL;

Step3: /* Projection of Ps_{i+1}, ... , Ps_{n} onto level i. */
        if (i < n) {
t = ACLOCK();
	  PPFLPROJ(Ps,i,P);
t = ACLOCK() - t;

//if (PCVERBOSE) { SWRITE("--PPFLPROJ   : "); IWRITE(t); SWRITE("\n"); }
	}
t = ACLOCK();


Step4: /* Loop over each level i section cell c. */
	for(S = PCADSCANL(Cs,i); S != NIL; S = RED(S)) {
	  FIRST3(FIRST(S),&bs,&cs,&ds);

Step5: /* Set L to a list of all level i projection factors 
of which c is a section. */
	  L = LPFSETMINUS(LPFZC(LELTI(cs,SC_REP),P),LPFZC(LELTI(bs,SC_REP),P));
	  for(Lp = L; (Lp != NIL) && (QPPPFL(FIRST(Lp),Ps) != 1);
	      Lp = RED(Lp));
	  if (Lp == NIL) {

Step6: /* Determine if cell c and its stack nieghbors have the 
same truth structure.  If not, add L to Q.  L represents a 
condition on the set of proj. pols. */
	    if (( ! CTSEQ(bs,cs)) || (! CTSEQ(cs,ds))) {
	      Q = COMP(L,Q); } } }


t = ACLOCK() - t;
//if (PCVERBOSE) { SWRITE("--BODY       : "); IWRITE(t); SWRITE("\n"); }

Step7: /* Find a minimum hitting set for Q. */
t = ACLOCK();
	T1 = PPFMINHITSET(Q,P,i);
t = ACLOCK() - t;
// if (PCVERBOSE) { SWRITE("--MINHIT     : "); IWRITE(t); SWRITE("\n"); }
	N = COMP(T1,N);

Step8: /* End of loop.  Set level i pruned proj fac's. 
Build ith level of Cs. */
t = ACLOCK();
	T2 = PFSUNION(T1,LELTI(Ps,i));
	SLELTI(Ps,i,T2);
	PLCAD(Cs,i,Ps,P);
t = ACLOCK() - t;
//if (PCVERBOSE) { SWRITE("--REFINE CAD : "); IWRITE(t); SWRITE("\n"); }
      }

Return:
      *Cs_ = Cs;
      *Ps_ = PFSREORDERREV(P,Ps);
      *N_  = N;
      return;
}
