#include "extlang.h"

void TEMPWR(Word D, Word i)
{
  Word j,L;

  for(j = 0; j < i; j++)
    SWRITE("     ");
  
  OWRITE(LELTI(LELTI(D,SC_REP),INDX));
  SWRITE(":");
  OWRITE(LELTI(D,SC_SIGN));
  SWRITE(":");
  OWRITE(LELTI(D,SC_EXTS));
  SWRITE(":");
  IWRITE(LELTI(D,SC_TMPM));
  SWRITE(":");
  if (ISATOM(LELTI(D,SC_CDTV))) {
    IWRITE(LELTI(D,SC_CDTV)); SWRITE("\n"); }
  else {
    SWRITE("\n");
    L = LELTI(D,SC_CDTV);
    while (L != NIL) {
      TEMPWR(FIRST(L),i+1);
      L = RED(L); } }
  return;
}
