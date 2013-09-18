/*======================================================================
                      L <- HAP1(U,V,w_l,B)

Half Stack Adjacency for 2D CAD cells, deal negative asymptotes.

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

Word HAP1(Word U, Word V, Word w_l, Word B)
{
  Word Sol,S,Solp,u,I,w_u;

Step1: /* Initialization. */
  if (U == NIL) {
    Sol = LIST1(NIL);
    goto Return; }
  Sol = NIL;
  S = NIL;

Step2: /* Loop trying more and more sections in U as asymptotes.*/
  do {
    Solp = HAP2(U,V,w_l,B);
    if (Solp != AD2D_FAIL)
      Sol = CCONC(ADD_2_SOL(S,Solp),Sol);
    if (U == NIL) break;
    ADV(U,&u,&U);
    FIRST2(u,&I,&w_u);
    S = COMP( LIST2(I,LIST2(B,AD2D_N_In)) , S );
  } while(VECTOR_LTEQ(w_u,w_l));
  if (Sol == NIL)
    Sol = AD2D_FAIL;
  
Return: /* Prepare to return. */
  return Sol;
}
