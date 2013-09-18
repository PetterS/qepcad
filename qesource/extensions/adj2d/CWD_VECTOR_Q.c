/*======================================================================
                      t <- CWD_VECTOR_Q(u,v)

Componant-wise disjoint vectors query.

Inputs
  u  : a list of BETA-digits.
  v  : a list of BETA-digits, LENGTH(u) = LENGTH(v).

Outputs
  t  : 1 if there is no componant on which both u and v are non-zero.
       0 otherwise.
======================================================================*/
#include "adj2D.h"
#include "adj2D.h"

Word CWD_VECTOR_Q(Word u, Word v)
{
  for(; u != NIL; u = RED(u), v = RED(v))
    if (FIRST(u) && FIRST(v))
      return 0;
  return 1;
}
