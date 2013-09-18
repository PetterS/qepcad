/* Extended sub-CAD cell write. */
#include "extlang.h"

void ESCELLWR(Word C)
{
  Word L,p,l;

  for(L = NIL, p = C; LELTI(p,SC_PAR) != NIL; p = LELTI(p,SC_PAR))
    L = COMP2(LELTI(p,SC_SIGN),LELTI(p,SC_EXTS),L);
  while(L != NIL) {
    SWRITE("[");
    for(ADV(L,&l,&L); l != NIL; l = RED(l)) {
      switch(FIRST(l)) {
      case POSITIVE: SWRITE("+"); break;
      case ZERO    : SWRITE("0"); break;
      case NEGATIVE: SWRITE("-"); break;
      case FNOTDEF : SWRITE("x"); break; } }
    SWRITE("] "); }
  OWRITE(LELTI(LELTI(C,SC_REP),INDX));

  SWRITE(" ");
  
  switch(LELTI(C,SC_CDTV)) {
  case TRUE : SWRITE("T"); break;
  case FALSE: SWRITE("F"); break;
  default:    SWRITE("U"); break; }

  SWRITE("\n");
  
  return;
}
