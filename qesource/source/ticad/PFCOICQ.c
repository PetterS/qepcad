/*======================================================================
          tr <- PFCOICQ(r,A,c,P,D)

Projection factor constant order in cylinder query.

Inputs
  r : a level
  A : an r-level saclib polynomial
  c : a cell of level less than r
  P : The qepcad data structure for the projection factors.
  D : the qepcad pcad data structure containing C

Outputs
Returns FALSE if the current CAPolicy does not support CONSTORDTEST,
which is needed for the computation.
Returns TRUE if it is determined that the vanishing of A and 
the elements of L, the list of projection factors that are zero
in cell c, implies that the order of A is constant.
Otherwise returns a GB for A,L and all k-order partials of A s.t.
some of the partials are not identical zero on V(L,A).
======================================================================*/
#include "qepcad.h"
#include "db/CAPolicy.h"

Word PFCOICQ(Word r, Word A, Word c, Word P, Word D)
{
  if (!GVCAP->supports("CONSTORDTEST")) { return FALSE; }
  Word L1 = LPFZCALL(c,P,D);
  Word L2 = LPFTOLRLP(r,L1);
  Word tr = GVCAP->CONSTORDTEST(r,A,L2);
  return tr;
}

