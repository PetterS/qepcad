/*======================================================================
                      t <- VECTOR_ODD_E(v)

Vector odd entries

Inputs
  v  : a list of BETA_digits.

Outputs
  t  : 1 if v has any odd entries, 0 otherwise.
======================================================================*/
#include "adj2D.h"
#include "adj2D.h"

Word VECTOR_ODD_E(Word v_)
{
  Word v;

  for(v = v_; v != NIL; v = RED(v))
    if (FIRST(v) % 2 == 1)
      return 1;

  return 0;
}
