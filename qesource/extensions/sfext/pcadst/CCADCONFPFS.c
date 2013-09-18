/*======================================================================
                      CCADCONFPFS(n,P,C;Ps,Cs)

Coarse CAD construction from projection factor subset.

Inputs
  n  : The dimension of the CAD.
  P  : The qepcad data structure for the projection factors.
  C  : The partial CAD.
  N  : A pruned projection factor data structure containing a subset
       of P sufficient for solution formula construction.

Outputs
  Ps : The qepcad data structure for projection factors, for the 
       pruned projection factors.
  Cs : The pruned partial CAD.

======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

void CCADCONFPFS(Word n, Word P, Word C, Word N, Word *Ps_, Word *Cs_)
{
      Word Ps,Cs,i,S;

Step1: /* Initialization: Set Ps to a list of n empty lists. */
      Ps = NIL; for(i = 0; i < n; i++) { Ps = COMP(NIL,Ps); }
      Cs = SCADDSCON(C,NIL,n);
      SLELTI(Ps,n,LELTI(N,n));

Step2: /* Loop over each i from n-1 down to 1. */
      PLCAD(Cs,n,Ps,P);
      for(i = n-1; i > 0; i--) {
	PPFLPROJ(Ps,i,P);
        S = PFSUNION(LELTI(N,i),LELTI(Ps,i));
        SLELTI(Ps,i,S);
        PLCAD(Cs,i,Ps,P); }

Return:
      *Cs_ = Cs;
      *Ps_ = PFSREORDERREV(P,Ps);
}
