/*======================================================================
                       Sol <- P3(U,V,W,v_l,B)

Program 3 driving adjaceny computation.

Inputs
  U  : the stack over c_(i-1), represented as Adj2D_Cells.
  V  : the stack over cell c_i for some section cell c_i, represented 
       as Adj2D_Cells.
  W  : the stack pver c_(i+1), represented as Adj2D_Cells.
  v_l: the characteristic vector for the set of level 2 polynomials
       whose leading coefficients vanish on c_i.
  B  : B = i, the index of the base cell of V.

Outputs
  Sol: a list (l_1, ... , l_n) where each l_j is a possible complete
       assignment of adjacencies between cells in U and V, and between
       cells of V and W.  Returns AD2D_FAIL if it fails.

Note:  Program 3 is the first called, and 
       1) checks for U & W empty, in which case the empty assignment
          is the only solution.
       2) Simply passes the problem on to Program 4 if there're no
          assymptotes.
       3) tries to find solutions with the first 0,1, ... cells in U
          as negative asymptotes.
======================================================================*/
#include "adj2D.h"

Word P3(Word U, Word V, Word W, Word v_l, Word B)
{
  Word I,J,Sol,S,u,As;

Step1: /* Special Case: No adjacencies to determine. */
  if (U == NIL && W == NIL)
    return LIST1(NIL);
  
Step2: /* Loop. */
  J = LIST2(B,AD2D_N_In); Sol = NIL; As = NIL;
  do{
    S = P4(U,V,W,v_l,B);
    if (S != AD2D_FAIL)
      Sol = CCONC( ADD_2_SOL(As,S) , Sol );
    if (U == NIL)
      break;
    ADV(U,&u,&U);
    As = COMP(LIST2(LELTI(u,AD2D_Index),J),As);
  }while( VECTOR_LTEQ(LELTI(u,AD2D_Mult),v_l) );
  
 Return: /* */
  if (Sol == NIL)  return AD2D_FAIL;
  return Sol;
}
