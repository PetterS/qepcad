/*======================================================================
                      L <- LPFTOLRLP(r,L)

List of projection factors to list of r-level polynomials

Inputs
  L : a list of qepcad projection factors
Outputs
  R : A list of the same polynomials, but as r-level saclib polynomials.
======================================================================*/
#include "qepcad.h"

Word LPFTOLRLP(Word r, Word L)
{
  Word R = NIL;
  for(Word Lp = L; Lp != NIL; Lp = RED(Lp))
  {
    Word P, rp, q;
    P = FIRST(Lp);
    rp = SECOND(LELTI(P,PO_LABEL));
    for(q = LELTI(P,PO_POLY); rp < r; rp++)
      q = LIST2(0,q);
    R = COMP(q,R);
  }
  return CINV(R);
}
