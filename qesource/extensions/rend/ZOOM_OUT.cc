/* xf, xy logarithmic binary rationals > 1. */
#include "rend.h"
 
Word ZOOM_OUT(Rend_Cell &M, Rend_Win &W, Word xf,
	      Word yf, Word N, Word P)
{
  Word mx,dx,dxp,dxp2,my,dy,dyp,dyp2,e;

  /***** Reset extents for x ******/
  mx = LBRNP2PROD( LBRNSUM(W.X.W, W.x.W) , -1);
  dx = LBRNDIF(W.X.W, W.x.W);
  dxp =  LBRNPROD( dx,xf );
  dxp2 = LBRNP2PROD( dxp , -1 );
  W.x.W = LBRNDIF( mx , dxp2 );
  W.X.W = LBRNSUM( mx , dxp2 );

  /***** Reset extents for y ******/
  my = LBRNP2PROD( LBRNSUM(W.Y.W, W.y.W) , -1);
  dy = LBRNDIF(W.Y.W, W.y.W);
  dyp = LBRNPROD( dy,yf );
  dyp2 = LBRNP2PROD( dyp , -1 );
  W.y.W = LBRNDIF( my , dyp2 );
  W.Y.W = LBRNSUM( my , dyp2 );

  W.update_extents(M);

  /******** Reset the precisions. *********/
  W.precis.x = -4 + LBRNQORD( dxp , ILBRN(W.pixdim.x) );
  W.precis.y = -4 + LBRNQORD( dyp , ILBRN(W.pixdim.y) );

  /******** Add points to edges if need be. **********/
  e = LBRNP2PROD(LBRNDIF(W.X.W,W.x.W),-ILOG2(N));
  if (LBRNCOMP( W.x.W , M[2].sample -> coordinate( W.precis.x ) ) < 0)
    FILL_2D(M,W,e,LIST1(1),P);
  if (LBRNCOMP( W.X.W , M[M.child.size() - 3].sample -> 
		coordinate( W.precis.x ) ) > 0)
    FILL_2D(M,W,e,LIST1(M.child.size() - 2),P);

  return e;
}
