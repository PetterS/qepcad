/*======================================================================

  t = 1 : means solution space closed.
  t = 2 : means non-solution space closed.
  t = 3 : means solution space is the closure of an open set.
======================================================================*/
#include "truthbytop.h"
#include "adj2D.h"

void TVCLOSURE1DS(Word D, Word P, Word J, Word k, Word t)
{
  Word S;

Step1: /*  */
  for(S = LELTI(D,CHILD); S != NIL; S = RED(S))
    TVCLOSURE1DS(FIRST(S),P,J,k,t);
  TVCLOSURE1D(D,P,J,k,t);

  return;
}
