/*======================================================================
                      S <- SOSRSUPS(L)

Set of Sets, remove supersets 

Inputs
  L  : a list of lists

Outputs
  S  : 
======================================================================*/
#include "qepcad.h"

Word SOSRSUPS(Word L)
{
  Word f,Lp,Q,M,S;
  if (L == NIL) return NIL;
  ADV(L,&f,&Lp);
  Lp = SOSRSUPS(Lp);

  Q = NIL;
  for(M = Lp; M != NIL && !SUBSET(FIRST(M),f); M = RED(M))
    if (!SUBSET(f,FIRST(M)))
      Q = COMP(FIRST(M),Q);
  
  if (M != NIL)
    S = Lp;
  else
    S = COMP(f,Q);

Return: /* Prepare to return */
  return S;
}
