/*======================================================================
                      N <- SUM_NORM_SP(v)

Sum norm "special"

Inputs
  v  : a list of BETA_digits.

Outputs
  N  : the sum norm of N under the assumption that the computation
       can be carried out without overflowing the "int" type.
======================================================================*/
#include "adj2D.h"
#include "adj2D.h"

Word SUM_NORM_SP(Word v)
{
  Word N;

  for(N = 0; v != NIL; v = RED(v))
    N += FIRST(v);

  return N;
}
