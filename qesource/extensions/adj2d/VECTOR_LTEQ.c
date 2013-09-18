/*======================================================================
                      t <-- VECTOR_LTEQ(u,v)

Vector less than or equal to.

Inputs
  u  : a list of BETA-digits.
  v  : a list of BETA-digits, LENGTH(u) = LENGTH(v).

Outputs
  t  : 1 if u is less than or equal to v in every position.
======================================================================*/
#include "adj2D.h"
#include "adj2D.h"

Word VECTOR_LTEQ(Word u, Word v)
{
  for(; u != NIL; u = RED(u), v = RED(v))
    if (FIRST(u) > FIRST(v))
      return 0;
  return 1;
}
