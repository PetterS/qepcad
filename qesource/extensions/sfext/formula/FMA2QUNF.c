/*===========================================================================
                             Fs <- FMA2QUNF(F,P)

FMA Formula to QEPCAD Unnormalized Formula

Inputs
  F : an FMA formula.
  P : the projection factor set to which F's indices refer

Outputs
  Fs: translation of F into QEPCAD's Unnormalized formula format.
===========================================================================*/
#include "qepcad.h"

Word FMA2QUNF(Word F, Word P)
{
  Word T =  FIRST(F), Fs;

  /* Translate TRUE and FALSE */
  if (T == TRUE) return LIST4(EQOP,0,0,NIL);
  if (T == FALSE) return LIST4(NEOP,0,0,NIL);

  /* Translate ANDOP and OROP */
  if (T == ANDOP || T == OROP) {
    Word Lp = NIL;
    for(Word L = CINV(RED(F)); L != NIL; L = RED(L))
      Lp = COMP(FMA2QUNF(FIRST(L),P),Lp);
    Fs = COMP(T,Lp);
    return Fs; }

  /* Atomic Formula */
  if (ISLIST(T)) {
    Word S = SECOND(F),i,j;
    FIRST2(T,&i,&j);
    Word p = LELTI(LELTI(LELTI(P,i),j),PO_POLY);
    if (ISATOM(S))
      Fs = LIST4(S,p,i,NIL);
    else {
      Word op,k;
      FIRST2(S,&op,&k);
      Fs = LIST6(IROOT,op,k,p,i,NIL); }
    return Fs;
  }

  /* Anything else is unexpected! */
  FAIL("FMA2QUNF","Unknown boolean operation or atomic formula type!");
  return 0;
}
