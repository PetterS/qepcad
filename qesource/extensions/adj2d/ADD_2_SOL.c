/*======================================================================
                      Sp <- ADD_2_SOL(a,S)

Add to solution.

Inputs
  a  : a list of adjacencies.
  S  : a list of solutions, where each solution is a list of
       adjacency.

Outputs
  Sp : a list of solutions, where each solution is a solution from
       S with the adjacencies in a attatched.
======================================================================*/
#include "adj2D.h"
#include "adj2D.h"

Word ADD_2_SOL(Word a, Word S)
{
  Word Sp;

  for(Sp = NIL; S != NIL; S = RED(S))
    Sp = COMP( CCONC(a,FIRST(S)) , Sp);

  return Sp;
}
