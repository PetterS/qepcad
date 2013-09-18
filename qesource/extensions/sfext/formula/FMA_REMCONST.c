/*

ForMulA remove constants

Note:  Need to add other operations

 */

#include "extlang.h"

Word FMA_REMCONST(Word F)
{
  Word f1,Fp,Q,L,G;

  f1 = FIRST(F);
  
  switch(f1) {
  case (ANDOP): /* ANDOP */
    Q = NIL;
    for(L = CINV(RED(F)); L != NIL; L = RED(L)) {
      G = FMA_REMCONST(FIRST(L));
      if (FIRST(G) == TRUE)
	continue;
      if (FIRST(G) == FALSE) {
	Fp = LIST1(FALSE);
	goto Return; }
      Q = COMP(G,Q); }
    if (Q == NIL) {
      Fp = LIST1(TRUE);
      goto Return; }
    Fp = COMP(ANDOP,Q);
    break;

  case (OROP): /* OROP */
    Q = NIL;
    for(L = CINV(RED(F)); L != NIL; L = RED(L)) {
      G = FMA_REMCONST(FIRST(L));
      if (FIRST(G) == FALSE)
	continue;
      if (FIRST(G) == TRUE) {
	Fp = LIST1(TRUE);
	goto Return; }
      Q = COMP(G,Q); }
    if (Q == NIL) {
      Fp = LIST1(FALSE);
      goto Return; }
    Fp = COMP(OROP,Q);
    break;

  default:
    Fp = F;
    break;
  }

 Return:
  return Fp;

}
