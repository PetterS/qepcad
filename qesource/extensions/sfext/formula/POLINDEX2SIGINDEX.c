/*===========================================================================
                             k <- POLINDEX2SIGINDEX(P_i,j)

Polynomial index to signiture index

Inputs
  P_i : a list of i-level polynomials.
  j   : an index, such that P_(i,j) is in P_i.

Outputs
  k   : such that the kth element of P_i is P_(i,j).
===========================================================================*/
#include "espcad.h"


Word POLINDEX2SIGINDEX(Word P_i, Word j)
{
  int k;
  for(k = 1; THIRD(LELTI(FIRST(P_i),PO_LABEL)) != j; P_i = RED(P_i),k++);
  return k;
}
