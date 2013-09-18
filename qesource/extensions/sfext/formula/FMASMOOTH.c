/*

ForMulA smooth.


 */

#include "extlang.h"

Word FMASMOOTH(Word F)
{
  Word G,F1,f,L,Fp;
  
Step1: /* Atoms and Constants. */
  F1 = FIRST(F);
  if (ISLIST(F1) || F1 == TRUE || F1 == FALSE) {
    G = F;
    goto Return; }

Step2: /* AND's */
  if (F1 == ANDOP) {
    L = NIL;
    for(Fp = CINV(RED(F)); Fp != NIL; Fp = RED(Fp)) {
      f = FMASMOOTH(FIRST(Fp));
      if (FIRST(f) == FALSE) {
	G = LIST1(FALSE);
	goto Return; }
      else if (FIRST(f) == TRUE)
	continue;
      else if (FIRST(f) == ANDOP)
	L = CCONC(RED(f),L);
      else
	L = COMP(f,L); }
    if (L == NIL)
      G = LIST1(TRUE);
    else if (LENGTH(L) == 1)
      G = FIRST(L);
    else
      G = COMP(ANDOP,L); }

Step3: /* OR's */
  if (F1 == OROP) {
    L = NIL;
    for(Fp = CINV(RED(F)); Fp != NIL; Fp = RED(Fp)) {
      f = FMASMOOTH(FIRST(Fp));
      if (FIRST(f) == TRUE) {
	G = LIST1(TRUE);
	goto Return; }
      else if (FIRST(f) == FALSE)
	continue;
      else if (FIRST(f) == OROP)
	L = CCONC(RED(f),L);
      else
	L = COMP(f,L); }
    if (L == NIL)
      G = LIST1(FALSE);
    else if (LENGTH(L) == 1)
      G = FIRST(L);
    else
      G = COMP(OROP,L); }
  
Return: /*Prepare to return. */
  return G;
}
