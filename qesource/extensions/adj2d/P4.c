/*======================================================================
                       Sol <- P4(U,V,W,v_l,B)

Program 4 driving adjaceny computation.

Inputs
  U  : the stack pver c_(i-1), represented as Adj2D_Cells.
  V  : the stack over cell c_i for some section cell c_i, represented 
       as Adj2D_Cells.
  W  : the stack pver c_(i+1), represented as Adj2D_Cells.
  v_l: the characteristic vector for the set of level 2 polynomials
       whose leading coefficients vanish on c_i.
  B  : B = i, the index of the base cell of V.

Outputs
  Sol: a list (l_1, ... , l_n) where each l_j is a possible complete
       assignment of adjacencies between cells in U and V, and between
       cells of V and W.

Notes: Program 4 tries to find solutions with zero, then the first 1,
       then the first 2, etc. cells of W as negative asymptotes.
       
======================================================================*/
#include "adj2D.h"

Word P4(Word U, Word V, Word W, Word v_l, Word B)
{
  Word I,Sol,S,w,As,J;

Step1: /* Loop. */
  J = LIST2(B,AD2D_N_In); Sol = NIL; As = NIL;
  do{
    S = P1(U,V,W,v_l,B);
    if (S != AD2D_FAIL)
      Sol = CCONC( ADD_2_SOL(As,S) , Sol );
    if (W == NIL) break;
    ADV(W,&w,&W);
    As = COMP(LIST2(J,LELTI(w,AD2D_Index)),As);
  }while(VECTOR_LTEQ(LELTI(w,AD2D_Mult),v_l));
  
Return: /* */
  if (Sol == NIL)  return AD2D_FAIL;
  return Sol;
}
