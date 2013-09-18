/*======================================================================
                      w <- ZERO_VECTOR(n)

Zero vector of length n.

Inputs
  n  : a BETA-digit

Outputs
  w  : a list of n zeros.
======================================================================*/
#include "adj2D.h"

Word ZERO_VECTOR(Word n)
{
  Word i,M;

  for(i = 0, M = NIL; i < n; i++)
    M = COMP(0,M);

  return M;
}
