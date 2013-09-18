/*

Existential propogation.

i : a level
C : a CAD cell.

Side Effects:

i-level cells are assigned truth values.  For i-level cell c, if
one of c's children is marked true, c will be marked true.
*/
#include "extlang.h"

void EXPROP(Word i, Word C)
{
  Word S,tf,uf,t;

Step1: /* Truth value determined and/or no children. */
  if ((S = LELTI(C,CHILD)) == NIL || LELTI(C,TRUTH) != UNDET)
    goto Return;

Step2: /* Level of C less than i. */
  if (LELTI(C,LEVEL) < i) {
    while(S != NIL) {
      EXPROP(i,FIRST(S));
      S = RED(S); }
    goto Return; }

Step3: /* Level of C is i. */
  for(tf = 0, uf = 0; S != NIL && !tf; S = RED(S)) {
    t = LELTI(FIRST(S),TRUTH);
    tf = (t == TRUE);
    uf |= (t != FALSE); }
  if (tf) {
    SLELTI(C,TRUTH,TRUE);
    SLELTI(C,HOWTV,BYPRP); }
  else if (!uf) {
    SLELTI(C,TRUTH,FALSE);
    SLELTI(C,HOWTV,BYPRP); }
    
Return: /* Prepare to return. */
  return;

}
