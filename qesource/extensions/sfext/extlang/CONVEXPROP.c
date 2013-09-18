/*

CONVEXPROP

i : a level
C : a CAD cell.

Side Effects:

i-level cells are assigned truth values.  For i-level cell c, if
one of c's children is marked true, c will be marked true.
*/
#include "extlang.h"

void CONVEXPROP(Word i, Word C)
{
  Word S,t,itc,ifc,flag;

Step1: /* Truth value determined and/or no children. */
  if ((S = LELTI(C,CHILD)) == NIL || LELTI(C,TRUTH) != UNDET)
    goto Return;

Step2: /* Level of C less than i. */
  if (LELTI(C,LEVEL) < i) {
    while(S != NIL) {
      CONVEXPROP(i,FIRST(S));
      S = RED(S); }
    goto Return; }

Step3: /* Level of C is i. */
  itc = 0; ifc = 0; flag = 0;
  for(; S != NIL && !flag; S = RED(S)) {
    t = LELTI(FIRST(S),TRUTH);
    if (itc == 0) {
      if (t == TRUE)
	itc = 1; }
    else if (t == FALSE) {
      ifc = 1; }
    else if (t == TRUE && ifc != 0) {
      flag = 1; } }

  if (flag) {
    SLELTI(C,TRUTH,TRUE);
    SLELTI(C,HOWTV,BYPRP); }
  else {
    SLELTI(C,TRUTH,FALSE);
    SLELTI(C,HOWTV,BYPRP); }
  
Return: /* Prepare to return. */
  return;

}
