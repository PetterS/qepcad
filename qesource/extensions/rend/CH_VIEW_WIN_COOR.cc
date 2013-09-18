/* xf,Xf,yf,Xf floats. */
#include "rend.h"
 
Word CH_VIEW_WIN_COOR(Rend_Cell &M, Rend_Win &W, Word P, Word N,
		 Word x,Word X, Word y, Word Y)
{
  Word e,L,i;

  W.x.W = x;
  W.X.W = X;
  W.y.W = y;
  W.Y.W = Y;

  W.update_extents(M);

  /******** Reset the precisions. *********/
  W.precis.x = LBRNQORD(LBRNDIF(W.X.W,W.x.W),ILBRN(W.pixdim.x)) - 3;
  W.precis.y = LBRNQORD(LBRNDIF(W.Y.W,W.y.W),ILBRN(W.pixdim.y)) - 3;

  /******** Add points to edges if need be. **********/
  e = LBRNFIE(1,LBRNQORD(LBRNDIF(W.X.W,W.x.W),ILBRN(N)));
  
  L = NIL;
  for(i = M.child.size() - 2; i > 0 ; i -= 2 )
    L = COMP(i,L);

  FILL_2D(M,W,e,L,P);

  return e;
}
