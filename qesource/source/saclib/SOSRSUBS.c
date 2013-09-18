/*======================================================================
                      S <- SOSRSUBS(L)

Set of Sets, remove subsets 

Inputs
  L  : a list of lists

Outputs
  S  : 
======================================================================*/
#include "qepcad.h"

Word SOSRSUBS(Word L)
{
  Word f,Lp,Q,M,S;
  if (L == NIL) return NIL;
  ADV(L,&f,&Lp);
  Lp = SOSRSUBS(Lp);

  Q = NIL;
  for(M = Lp; M != NIL && !SUBSET(f,FIRST(M)); M = RED(M))
    if (!SUBSET(FIRST(M),f))
      Q = COMP(FIRST(M),Q);
  
  if (M != NIL)
    S = Lp;
  else
    S = COMP(f,Q);

Return: /* Prepare to return */
  return S;
}
