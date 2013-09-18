/*===========================================================================
                       FILL_2D(M,W,e,L,P)

Fill in the 2D sections over sectors.

Inputs
  M : The Rend_Cell cell structure for the CAD.
  W : The Rend_Win structure defining the viewing infromation.
  e : A logarithmic binary number giving the offset for the
      x sample points.
  L : A list of indices of 1D section cells in which points should
      be added.
  P : The qepcad projection factor data structure.
===========================================================================*/
#include "rend.h"

void FILL_2D( Rend_Cell &M, Rend_Win &W, Word e, Word L, Word P )
{
  Word Lp,i,I,ap,bp,a,b,Lb,p_n,n,A,Q,yl,x,j,c,cp,Qp;

Step1: /* Add the points. */
  for(Lp = L; Lp != NIL; Lp = RED(Lp) ) {
    //-- Get index for base cell of stack
    i = FIRST(Lp);
    if (M[i].child.size() < 3)
      continue; //-- no stack

    //-- clear points for all section cells in stack
    for( j = 2; j < M[i].child.size() - 1; j+= 2 )
      ((Rend_Sample_2DC*)M[i][j].sample) -> clear_points();

    //-- get the interval you want to fill
    I = M[i].sample -> coordinate( W.precis.x );
    FIRST2(I,&ap,&bp);
    if (i == 1)
      ap = LBRNDIF(ap,e); //-- ensure that we draw to right edge.
    if (i == M.child.size() - 2)
      bp = LBRNSUM(bp,e); //-- ensure that we draw to right edge.
    a = LBRNRN(ap);  b = LBRNRN(bp);

    //-- c = NIL if b-a > e, otherwise c is the midpoint of (a,b)
    if ( LBRNCOMP( LBRNDIF(bp,ap) , e) < 1 ) {
      cp = LBRNP2PROD( LBRNSUM(ap,bp) , -1 );
      c = LBRNRN(cp); }
    else
      c = NIL;

Step2: /* Loop over each level 2 proj factor. */
    for(Lb = SECOND(P); Lb != NIL; Lb = RED(Lb)) { 
      p_n = FIRST(Lb);
      n = THIRD( LELTI(p_n,PO_LABEL) );
      A = LELTI(p_n,PO_POLY);
      if (c == NIL) {
	Q = IBPPOS(A,a,b,LBRNRN(e), -W.precis.y);
	Q = CINV(Q); }
      else {
	Qp = IBPPOL(A,c,-W.precis.y);
	if (Qp == NIL)
	  Q = NIL;
	else
	  Q = LIST2(Qp,cp); }
      
Step3: /* Add new points to CAD for P_(2,n). */
      while(Q != NIL) {
	ADV2(Q,&yl,&x,&Q);
	ADD_POINTS( M[i],n,x,yl ); } } }

  return;
}
