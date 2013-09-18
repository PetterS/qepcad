/*======================================================================
            Sol <- P1(U,V,W,v_l,B)

Program 1 driving adjaceny computation.

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

Notes: P1 has three main cases to deal with. 1) V is empty.  2) No
       singularities or vertical tangents at the next element of V.
       3) Singularities or vertical tangents at the next element of V.
======================================================================*/
#include "adj2D.h"

Word P1(Word U, Word V, Word W, Word v_l, Word B)
{
  Word Sol,As,S,u,I,J,a,w,v,n,x,x_u,x_w,N,m_v,m_2v;

  Sol = NIL; As = NIL;

Step1: /* No cells left in V. */
  if (V == NIL) {

    while(U != NIL) {
      ADV(U,&u,&U);
      if (VECTOR_LTEQ( LELTI(u,AD2D_Mult) , v_l )) {
	I = LELTI(u,AD2D_Index);
	J = LIST2(FIRST(I) + 1, AD2D_Infy);
	a = LIST2(I,J);
	As = COMP(a,As); }
      else
	return AD2D_FAIL; }

    while(W != NIL) {
      ADV(W,&w,&W);
      if (VECTOR_LTEQ( LELTI(w,AD2D_Mult) , v_l )) {
	I = LELTI(w,AD2D_Index);
	J = LIST2(FIRST(I) - 1, AD2D_Infy);
	a = LIST2(J,I);
	As = COMP(a,As); }
      else
	return AD2D_FAIL; }

    Sol = LIST1(As);
    goto Return; }

Step2: /* V not empty. */
  ADV(V,&v,&V);
  n = LENGTH(v_l);

Step3: /* Fill up all multiplicities of order 1. */
  x_u = ZERO_VECTOR(n); x_w = ZERO_VECTOR(n); m_v = LELTI(v,AD2D_Mult);
  
  while( ! EQUAL_ON_ONES(x_u,m_v) ) {
    if (U == NIL) return AD2D_FAIL;
    ADV(U,&u,&U);
    x_u = VECTOR_SUM(x_u,LELTI(u,AD2D_Mult));
    As = COMP( LIST2(LELTI(u,AD2D_Index),LELTI(v,AD2D_Index)) , As); }

  while( ! EQUAL_ON_ONES(x_w,m_v) ) {
    if (W == NIL) return AD2D_FAIL;
    ADV(W,&w,&W);
    x_w = VECTOR_SUM(x_w,LELTI(w,AD2D_Mult));
    As = COMP( LIST2( LELTI(v,AD2D_Index) , LELTI(w,AD2D_Index) ), As); }

Step4: /* In filling all these up, did I make mistakes? */
  m_2v = VECTOR_S_PROD(2,m_v);
  x = VECTOR_SUM(x_u,x_w);

  switch(VECTOR_SEMI_COMP(x,m_2v)) {
  case -1 : /* incomparable or x > m_2v. */
    return AD2D_FAIL;
  case  0 : /* x equals m_2v. */
    Sol = P1(U,V,W,v_l,B);
    if (Sol != AD2D_FAIL)
      Sol = ADD_2_SOL(As,Sol);
    break;
  case  1 : /* some multiple zero cells have not been filled. */
    V = COMP(v,V);
    do {
      S = P2(x_u,x_w,U,V,W,v_l,B);
      if (S != AD2D_FAIL)
	Sol = CCONC( ADD_2_SOL(As,S) , Sol );
      if (U == NIL) break;
      ADV(U,&u,&U);
      x_u = VECTOR_SUM(x_u,LELTI(u,AD2D_Mult));
      As = COMP( LIST2(LELTI(u,AD2D_Index),LELTI(v,AD2D_Index)) , As);
    } while( Mystery_f(x_u,x_w,m_v) );
  }

Return: /* */
  if (Sol == NIL)  return AD2D_FAIL;
  return Sol;
}
