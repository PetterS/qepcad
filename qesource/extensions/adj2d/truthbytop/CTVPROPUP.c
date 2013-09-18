/*======================================================================
                           CTVPROPUP(C,t,N,by)

Cell truth values propogate up.

Inputs
C  : A CAD cell
t  : C's truth-value
N  : A level in the CAD
by : A value for the HOWTV field.

Side Effects:  If C has level N, then its truth value is set to t,
and its HOWTV field is set to by.

======================================================================*/
#include "truthbytop.h"
#include "adj2D.h"

void CTVPROPUP(Word C, Word t, Word N, Word by)
{
  Word S,tp;

Step1: /* Change truth value if appropriate. */
  if (LELTI(C,LEVEL) == N) {
    if (t != UNDET && LELTI(C,TRUTH) == UNDET) {
      SLELTI(C,TRUTH,t);
      SLELTI(C,HOWTV,by); }
    if (t != UNDET)
      SLELTI(C,CHILD,NIL);
    goto Return; }

Step2: /* Propogate up. */
  if (t != UNDET)
    tp = t;
  else
    tp = LELTI(C,TRUTH);
  for(S = LELTI(C,CHILD); S != NIL; S = RED(S))
    CTVPROPUP(FIRST(S),tp,N,by);
  
Return: /* Prepare to return. */
  return;
}
