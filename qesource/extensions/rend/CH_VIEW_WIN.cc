/* Xa,Xt,Ys,Yt logarithmic binary rationals. */
#include "rend.h"
 
Word CH_VIEW_WIN(Rend_Cell &M, Rend_Win &W, Word Xs, Word Xt,
	      Word Ys,Word Yt, Word e, Word P)
{
  Word mx,dx,dxp,dxp2,my,dy,d2x,d2y,L,i;

  mx = LBRNP2PROD( LBRNSUM(W.x.W,W.X.W) , -1 );
  my = LBRNP2PROD( LBRNSUM(W.y.W,W.Y.W) , -1 );
  d2x = LBRNP2PROD( LBRNDIF(W.X.W,W.x.W) , -1 );
  d2y = LBRNP2PROD( LBRNDIF(W.Y.W,W.y.W) , -1 );

  mx = LBRNSUM(mx,Xt);
  my = LBRNSUM(my,Yt);
  d2x = LBRNPROD(Xs,d2x);
  d2y = LBRNPROD(Ys,d2y);

  W.x.W = LBRNDIF(mx,d2x);
  W.X.W = LBRNSUM(mx,d2x);
  W.y.W = LBRNDIF(my,d2y);
  W.Y.W = LBRNSUM(my,d2y);

  W.update_extents(M);

  /******** Reset the precisions. *********/
  W.precis.x += LBRNQORD(Xs,ILBRN(1));
  W.precis.y += LBRNQORD(Ys,ILBRN(1));

  /******** Add points to edges if need be. **********/
  e = LBRNPROD(e,Xs);
  
  L = NIL;
  for(i = M.child.size() - 2; i > 0 ; i -= 2 )
    L = COMP(i,L);

  FILL_2D(M,W,e,L,P);

  return e;
}
