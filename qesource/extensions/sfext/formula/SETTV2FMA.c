/*

Set truth value to formula.

k : the level of D

*/

#include "espcad.h"


void SETTV2FMA(Word D, Word P, Word F, Word k)
{
  Word Ds,EDs;
  Ds = SCADDSCON(D,NIL,k);
  EDs = PCAD2ESPCAD(P,P,Ds,NIL);
  SETMARK2FMA(EDs,F,P);
  SETCADTV2MARK(EDs);
  return;
}

