/*======================================================================
                      w <-- VECTOR_NEG(u)

Vector negative.

Inputs
  u  : a list of BETA-digits.

Outputs
  w  : a list of BETA-digits of length LENGTH(u).  Each componant of
       w is the negative of the corresponding componant of u.
======================================================================*/
#include "adj2D.h"
#include "adj2D.h"

Word VECTOR_NEG(Word u)
{
  Word s,w;

  for(s = NIL; u != NIL; u = RED(u))
    s = COMP(-FIRST(u),s);
  w = INV(s);

  return w;
}
