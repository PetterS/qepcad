/*======================================================================
                      w <- VECTOR_S_PROD(s,v)

Vector scalar product.

Inputs
  s  : a BETA-digit
  v  : a list of BETA-digits

Outputs
  w  : a list of BETA-digits s.t. w_i = s * v_i;
======================================================================*/
#include "adj2D.h"

Word VECTOR_S_PROD(Word s, Word v)
{
  Word w,wp;

  for(wp = NIL; v != NIL; v = RED(v))
    wp = COMP(s * FIRST(v) , wp );
  w = INV(wp);
  return w;
}
