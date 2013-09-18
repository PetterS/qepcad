/* List of level i factors of input polynomials. */
#include "qepcad.h"

Word LLIFIP(Word P, Word i, Word n)
{
      Word L,p,P_i;

Step1: /* Initialize. */
      L = NIL;

Step2: /* Construct. */      
      for(P_i = LELTI(P,i); P_i != NIL; P_i = RED(P_i)) {
	p = FIRST(P_i);
	if (FIRST(FIRST(LELTI(p,PO_LABEL))) == 'A')
	  L = COMP(p,L); }

Return: /* Return. */
      return (L);
}
