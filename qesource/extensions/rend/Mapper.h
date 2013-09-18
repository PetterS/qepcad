/*************************************************************
 **
 **  Mapper.h
 **
 **  A Mapper object represents a mapping taking points from
 **  some rectangle [x,X]x[y,Y], where x,X,y,Y are logarithmic
 **  binary rational numbers, (this is the "view rectangle")
 **  and mapping them to the rectangle [x1,x2]x[y1,y2] (this
 **  is the "rend"rectangle).
 **
 *************************************************************/
#ifndef _MAPPER_
#define _MAPPER_

#include "rend.h"
#include <iomanip>
#include <cmath>
using namespace std;

class Rend_Win;

class Mapper
{
 private:
  gcmemloc Sx, Kx, Sy, Ky;  // These store the transformation
  gcmemloc ux, uX, uy, uY;  // These store the "view rectangle" coordinates as rationals
 public:
  Mapper(int x1, int y1, int x2, int y2, Rend_Win &W)
  {
    Sx.W = RNQ(RNINT(x2 - x1),LBRNRN(LBRNDIF(W.X.W,W.x.W)));
    Kx.W = RNDIF(RNINT(x1),RNPROD(Sx.W,LBRNRN(W.x.W)));

    Sy.W = RNQ(RNINT(y2 - y1),LBRNRN(LBRNDIF(W.Y.W,W.y.W)));
    Ky.W = RNDIF(RNINT(y1),RNPROD(Sy.W,LBRNRN(W.y.W)));
    ux.W = RNINT(x1); 
    uX.W = RNINT(x2);
    uy.W = RNINT(y1);
    uY.W = RNINT(y2);
  }
  Word mapX(Word r)
  {
    return RNSUM(RNPROD(Sx.W,LBRNRN(r)),Kx.W);
  }
  Word mapY(Word r)
  {
    return RNSUM(RNPROD(Sy.W,LBRNRN(r)),Ky.W);
  }
  
  /*************************************************
   * constrain(x,L,U) constrains x.  Note: must have L < U.
   * Let w be the width of the interval (L,U).  The return
   * value constrains x to (L-w,U+w).
   *************************************************/
  Word constrain(Word x, Word L, Word U)
  {
    Word xp = x;
    Word D = RNDIF(U,L);
    Word LL = RNDIF(L,D);
    Word UU = RNSUM(U,D);
    if (RNCOMP(x,LL) < 0)
      xp = LL;
    else if (RNCOMP(x,UU) > 0)
      xp = UU;
    return xp;
  }

  void Xwrite(Word r, ostream &out, int p)
  {
    Word A,Ap;
    A = constrain(mapX(r),ux.W,uX.W);
    out << setprecision(p);
    Ap = RNPROD(A,RNP2(p));
    out << double(RNFLOR(Ap)) / pow(2.0,p);
  }
  void Ywrite(Word r, ostream &out, int p)
  {
    Word A,Ap;
    A = constrain(mapY(r),uy.W,uY.W);
    out << setprecision(p);
    Ap = RNPROD(A,RNP2(p));
    out << double(RNFLOR(Ap)) / pow(2.0,p);
  }
  void Pwrite(Word r, ostream &out, int p)
  {
    Word x,y;
    FIRST2(r,&x,&y);
    Xwrite(x,out,p);
    out << " ";
    Ywrite(y,out,p);
  }
  void LPwrite(Word L, ostream &out, int p, int flag = 0)
  {
    out << "newpath\n";
    Pwrite(FIRST(L),out,p);
    out << " moveto\n";
    for(L = RED(L); L != NIL; L = RED(L)) {
      Pwrite(FIRST(L),out,p);
      out << " lineto\n"; }
    if (flag)
      out << "fill" << endl;
    else
      out << "stroke" << endl;
  }
};


#endif /* _MAPPER_ */
