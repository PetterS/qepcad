/*

Set CAD truth values to mark.

*/
#include "extlang.h"

void SETCADTV2MARK(Word D)
{
  Word L,c;

  SLELTI(LELTI(D,SC_REP),TRUTH,LELTI(D,SC_TMPM));

  L = LELTI(D,SC_CDTV);
  if (ISLIST(L)) {
    while(L != NIL) {
      ADV(L,&c,&L);
      SETCADTV2MARK(c); } }

  return;
}
