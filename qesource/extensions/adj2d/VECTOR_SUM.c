/*======================================================================
                      w <-- VECTOR_SUM(u,v)

Vector sum.

Inputs
  u  : a list of BETA-digits.
  v  : a list of BETA-digits, LENGTH(u) = LENGTH(v).

Outputs
  w  : a list of BETA-digits of length LENGTH(u).  Each componant of
       w is the sum of componants of u and v.
======================================================================*/
#include "adj2D.h"
#include "adj2D.h"

Word VECTOR_SUM(Word u, Word v)
{
  Word s,w;

  for(s = NIL; u != NIL; u = RED(u), v = RED(v))
    s = COMP(FIRST(u) + FIRST(v),s);
  w = INV(s);

  return w;
}
