/*======================================================================
                      L <- HAP3(U,V,w_l,B)

Half Stack Adjacency for 2D CAD cells, deal positive asymptotes.

Inputs
  U  : the stack over c_(i-1), represented as Adj2D_Cells.
  V  : the stack over section cell c_(i), represented as Adj2D_Cells.
  w_l: the characteristic vector for the set of level 2 polynomials
       whose leading coefficients vanish on c_i.
  B  : B = i, the index of the base cell of V.

Outputs
  L  : a list of elements of the form ((i,j),(k,l))
       indicating an adjacency between cell (i,j) and cell (k,l).
======================================================================*/
#include "newadj2D.h"

Word HAP3(Word U, Word w_l, Word B)
{
  Word Sol,u,I,w_u,r,c1,c2;

Step1: /* Initialization. */
  if (U == NIL) {
    Sol = LIST1(NIL);
    goto Return; }

  ADV(U,&u,&U);
  FIRST2(u,&I,&r);
  Sol = LIST1(LIST2(I,LIST2(B,AD2D_Infy)));

  while(U != NIL) {
    ADV(U,&u,&U);
    FIRST2(u,&I,&w_u);
    r = VECTOR_SUM(r,w_u);
    Sol = COMP(LIST2(I,LIST2(B,AD2D_Infy)),Sol); }
  while(r != NIL) {
    ADV(r,&c1,&r);
    ADV(w_l,&c2,&w_l);
    if (c1 != 0 && c2 == 0) {
      Sol = AD2D_FAIL;
      goto Return; } }
  Sol = LIST1(Sol);

Return: /* Prepare to return. */
  return Sol;
}
