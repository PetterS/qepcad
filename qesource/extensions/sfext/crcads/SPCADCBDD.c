/*======================================================================
                      O <- SPCADCBDD(L)

Sort pruned-CAD cells by decreasing dimension.

Input
  L : a list of pruned-CAD cells.
  d : the level of the cells in L

Output
  O : a list of the same cells as in L, but sorted by decreasing
      dimension.
  
======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"


Word SPCADCBDD(Word L, Word d)
{
      Word S,i,c,O;

Step1: /* Prepare S, the list of buckets for bucket sort. */
      for(S = NIL,i = 0; i < d + 1; i++)
	S = COMP(NIL,S);

Step2: /* Put each cell in the proper bucket. */
      while(L != NIL) {
	ADV(L,&c,&L);
	i = CELLDIM(LELTI(c,SC_REP)) + 1;
	SLELTI(S,i,COMP(c,LELTI(S,i))); }

Step3: /* Concatenate buckets. */
      for(O = NIL; S != NIL; S = RED(S))
	O = CONC(FIRST(S),O);

Return: /* Return. */
  return O;
}
