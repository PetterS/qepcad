/*======================================================================
                      L <- HAS_CONS(c,P)

Half-stack adjacency Adj2D_Stack construct.

Inputs
  c : a cell of the 1D CAD.
  P : the projection factor set.

Outputs
  L : the stack over c represented as Adj2D_Cells.
======================================================================*/
#include "newadj2D.h"

Word HAS_CONS(Word c, Word P)
{
  Word L_c,L_s,L;

Step1: /* Initialize. */
  L_c = LELTI(c,CHILD); /* L_c = Stack over c. */
  if (L_c == NIL) return NIL;
  L_s = NIL;

Step2: /* Set L_s to the list of all section cells over c. */
  do {
    L_c = RED(L_c);
  if (L_c == NIL) break;
    L_s = COMP(FIRST(L_c),L_s);
    L_c = RED(L_c);
  }while(1);
  
Step3: /* Convert all sections to HA_Cell representations. */
  for(L = NIL; L_s != NIL; L_s = RED(L_s))
    L = COMP( HAC_CONS( FIRST(L_s) , P ) , L );

Return: /* Prepare to return. */
  return L;
}
