/*************************************************************
 **
 **  Rend_Win.h
 **
 **  A "Rend_Win" object captures the correspondence between 
 **  the "view window" and the "rend window". The "view window"
 **  is the rectangle in the cartesian plane that is to be
 **  represented in the "rend window", which is a rectangle of
 **  pixels on the screen.
 **
 *************************************************************/
#ifndef _REND_WIN_
#define _REND_WIN_

/*************************************************************
 **  Includes
 *************************************************************/
#include "rend.h"

/*************************************************************
 **  class Int_Pair
 *************************************************************/
class Int_Pair
{
 public:
  int x,y;
  Int_Pair(int c1= AD2D_ErrI,int c2 = AD2D_ErrI)
    { x = c1; y = c2; return; }
  int operator==(Int_Pair p) { return (x == p.x && y == p.y); }
  void set(const int &a, const int &b) { x = a; y = b; }
};


/*************************************************************
 **  class Rend_Win
 *************************************************************/
class Rend_Win
{
public:
  Int_Pair pixdim; /* pixel dimensions of drawing area       */
  Int_Pair margin; /* margin widths in pixels                */
  Int_Pair precis; /* 2^x x-precision, and 2^y y-precision   */
  gcmemloc x,X,y,Y;/* binary rational coord's of view area   */

  Rend_Win(Rend_Cell &D, int a = 400, int b = 400, 
	   Word ix = 0, Word iX = 0, Word iy = 0, 
	   Word iY = 0);
  Rend_Win(Rend_Win &W) : x(W.x), y(W.y), 
                          X(W.X), Y(W.Y) 
  { 
    pixdim = W.pixdim;
    margin = W.margin;
    precis = W.precis;
  }
  void defaulted(Rend_Cell &D, int a = 400, 
		 int b = 400, int ew = -3);
  void set_precis_faithfull();
  void update_extents(Rend_Cell &M);
  int SPEC_RNFLOR(Word a);
  int map_x(Word b);
  int map_y(Word b);
  void write_header(ostream &out);
  Word get_lociva(Rend_Cell &M);
};







#endif /* _REND_WIN_ */
