/*======================================================================
                      t <-- VECTOR_SEMI_COMP(u,v)



Inputs
  u  : a list of BETA-digits.
  v  : a list of BETA-digits, LENGTH(u) = LENGTH(v).

Outputs
  t  : 1 if u is less than v in every position.
       0 if u is equal to v in every position.
      -1 if u anf v are incmparable or v less than u in every position.
======================================================================*/
#include "adj2D.h"

Word VECTOR_SEMI_COMP(Word u, Word v)
{
  if ( VECTOR_LTEQ(u,v) )
    if ( VECTOR_LTEQ(v,u) )
      return 0;
    else
      return 1;
  else
    return -1;
}
