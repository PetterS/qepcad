/*======================================================================
                      CCADCON(n,P,C;Ps,Cs)

Coarse CAD construction.

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

void CCADCON(Word n, Word P, Word C, Word *Ps_, Word *Cs_)
{
  Word dummy;
  CCADCONEXT(n,P,C,Ps_,Cs_,&dummy);
}
