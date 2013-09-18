/*======================================================================
Cell cylinder truth value.               
======================================================================*/
#include "truthbytop.h"
#include "truthbytop.h"

Word CCTV(Word C)
{
  Word t,S;

Step1: /* Special cases. */
  t = LELTI(C,TRUTH);
  S = LELTI(C,CHILD);
  if (t != UNDET || S == NIL)
    goto Return;

Step2: /* Check truth values of children. */
  t = CCTV(FIRST(S));
  S = RED(S);
  while(S != NIL && t != UNDET) {
    if (t != CCTV(FIRST(S)))
      t = UNDET;
    S = RED(S); }
	    
Return: /* Prepare to return. */
  return t;
}
