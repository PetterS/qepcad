/*======================================================================
                      t <- EQUAL_ON_ONES(u,v)

Equal on ones.  NOTE THIS IS NOT SYMMETRIC!!!

Inputs
  u  : a list of BETA-digits
  v  : a list of BETA-digits, LENGTH(u) = LENGTH(v)

Outputs
  t  : 1 if [ (v_i == 1) ==> (u_i == 1) ], false otherewise.
======================================================================*/
#include "adj2D.h"
#include "adj2D.h"

Word EQUAL_ON_ONES(Word u, Word v)
{
  Word v_i,u_i;

  while( v != NIL ) {
    ADV(v,&v_i,&v);
    ADV(u,&u_i,&u);
    if ( (v_i == 1) && (u_i != 1 ) )
      return 0; }

  return 1;
}
