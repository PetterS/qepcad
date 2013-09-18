/*======================================================================
                    ESCSLKMF(C,k)

ESCAD Set level k marks to FALSE

Inputs
C : an ESCAD cell.
k : a level in the ESCAD.

Side Effects
All SC_TMPM marks in C at level k are set to FALSE.
======================================================================*/
#include "extlang.h"

void ESCSLKMF(Word C, Word k)
{
  Word S;

Step1: /* Mark if k is zero, otherwise recurse on children. */
  if (k == 0)
    SLELTI(C,SC_TMPM,FALSE);
  else {
    S = LELTI(C,SC_CDTV); 
    if (ISLIST(S)) {
      for(; S != NIL; S = RED(S))
	ESCSLKMF(FIRST(S),k-1); } }

Return: /* Prepare to return. */
    return;
}
