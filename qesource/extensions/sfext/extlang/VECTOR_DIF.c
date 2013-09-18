/*======================================================================
                      w <-- VECTOR_DIF(u,v)

Vector difference.

Inputs
  u  : a list of BETA-digits.
  v  : a list of BETA-digits, LENGTH(u) = LENGTH(v).

Outputs
  w  : a list of BETA-digits of length LENGTH(u).  Each componant of
       w is the difference of componants of u and v.
======================================================================*/
#include "qepcad.h"

Word VECTOR_DIF(Word u, Word v)
{
  Word s,w;

  for(s = NIL; u != NIL; u = RED(u), v = RED(v))
    s = COMP(FIRST(u) - FIRST(v),s);
  w = INV(s);

  return w;
}
