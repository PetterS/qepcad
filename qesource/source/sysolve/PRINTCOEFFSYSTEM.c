/*======================================================================
                    PRINTCOEFFSYSTEM(r,S)

Input
  r : a BDigit
  S : a system of polynomials
======================================================================*/
#include "qepcad.h"

static Word VarList;
void SETdummy(Word V) { VarList = V; }

void PRINTCOEFFSYS(BDigit r, Word S, Word Vp)
{
  Word V, Sp, L;
  SWRITE("\n");
  if (S == 1) {
    SWRITE("system is inconsistent\n\n");
    goto Return; }

  if (!Vp)
    V = VarList;
  else
    V = Vp;

  for(Sp = S; Sp != NIL; Sp = RED(Sp))
  {
    for(L = FIRST(Sp); L != NIL; L = RED(L))
    {
      IPDWRITE(r,FIRST(L),V);
      SWRITE("\n");
    }
    SWRITE("\n");
  }
  
 Return: /* Prepare to return */
  return;
}
