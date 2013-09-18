/*************************************************************
 **
 **  Rend_Win.cc
 **
 **
 *************************************************************/
#include "Rend_Win.h"

Rend_Win::Rend_Win(Rend_Cell &D, int a, int b, Word ix, Word iX, Word iy, Word iY)
{
  if (ix != iX) {
    Word t1,t2;
    pixdim.x = a; pixdim.y = b;
    margin.x = 0; margin.y = 0;
    x.W = ix;
    X.W = iX;
    y.W = iy;
    Y.W = iY;
    RNFCL2(RNPROD(LBRNRN(LBRNDIF(iX,ix)),RNRED(1,a)),&t1,&t2);
    precis.x = t1 - 3;
    RNFCL2(RNPROD(LBRNRN(LBRNDIF(iY,iy)),RNRED(1,b)),&t1,&t2);
    precis.y = t1 - 3; 

    D.set_extents(LIST2(x.W,X.W));
    for(int i = 0; i < D.child.size(); i++)
      D[i].set_extents(LIST2(y.W,Y.W)); }
  else {
    defaulted(D,a,b,-3); }
}

//-- This is a default constructor, that will try to fit the
//-- entire CAD into a nice square window with fixed deimension.
void Rend_Win::defaulted(Rend_Cell &D,int a, int b, int ew)
{
  Word t,k,min,max;
  Word ct,c2,d,dp,i;

  pixdim.x = a; pixdim.y = b;
  margin.x = 0; margin.y = 0;

  //-- find x-coordinates of view area. --//
  t = D.child.size() - 3;
  k = -2;
  if (t <= 2) {
    dp = (t == 2) ? D[t].sample -> coordinate(k) : 0;
    d = LBRNFIE(1,k-1);
    ct = LBRNSUM(dp,d);
    c2 = LBRNDIF(dp,d); }
  else  
    do{
      k -= 2;
      ct = D[t].sample -> coordinate(k);
      c2 = D[2].sample -> coordinate(k);
      d = LBRNDIF(ct,c2);
      //-- want:  e / d < 1 / pixdim.x , where e = 2^k. --//
    } while (LBRNCOMP( LBRNFIE(pixdim.x,k) , d ) > 0);
  
  dp = LBRNP2PROD(d,ew); //-- This is arbitrary. It says that
  x.W = LBRNDIF(c2,dp);    //-- the region left and right of the
  X.W = LBRNSUM(ct,dp);    //-- last single point cell will be 1/8
                         //-- of the interior in width.

  //-- find y-coordinates of view area. --//
  for(i = 2; i < D.child.size(); i += 2) {
    t = D[i].child.size() - 3;
    if (t >= 2)
      break; }

  //-- Special case 1: No single point cells found!! --//
  if ( i >= D.child.size() ) {
    /*    cerr << "Couldn't find any single point cells!" << endl
	 << "Setting default view window to [-1,1]^2" << endl;
    x.W = LIST2(-1,0);
    X.W = LIST2(1,0);
    y.W = LIST2(-1,0);
    Y.W = LIST2(1,0); */
    y.W = x.W;
    Y.W = X.W;
    goto SETEXT;
    return; }

  //-- Special case 2: first nonempty cylinder has a single section. --//
  if ( t == 2 ) {
    dp = D[i][t].sample -> coordinate(k);
    d = LBRNFIE(1,k-1);
    max = LBRNSUM(dp,d);
    min = LBRNDIF(dp,d); }
  else {
    k = -2; 
    do{
      k -= 2;
      ct = D[i][t].sample -> coordinate(k);
      c2 = D[i][2].sample -> coordinate(k);
    d = LBRNDIF(ct,c2);
    //-- want:  e / d < 1 / pixdim.y , where e = 2^k. --//
    } while (LBRNCOMP( LBRNFIE(pixdim.y,k) , d ) > 0);
    min = c2;
    max = ct; }
 
  for(i += 2; i < D.child.size() - 2; i += 2) {
    t = D[i].child.size() - 3;
    if (t >= 2) {
      if ( t == 2 ) {
	dp = D[i][t].sample -> coordinate(k);
	d = LBRNFIE(1,k-1);
	ct = LBRNSUM(dp,d);
	c2 = LBRNDIF(dp,d); }
      else {
	ct = D[i][t].sample -> coordinate(k);
	c2 = D[i][2].sample -> coordinate(k); }
      if (LBRNCOMP(c2,min) < 0)
	min = c2;
      if (LBRNCOMP(ct,max) > 0)
	max = ct;
    }
  }

  d = LBRNDIF(max,min);
  dp = LBRNP2PROD(d,ew);  //-- This is arbitrary. It says that
  y.W = LBRNDIF(min,dp);    //-- the region above and below the
  Y.W = LBRNSUM(max,dp);    //-- last single point cell will be 1/8
                          //-- of the interior in height.

 SETEXT:
  D.set_extents(LIST2(x.W,X.W));
  for(i = 0; i < D.child.size(); i++)
    D[i].set_extents(LIST2(y.W,Y.W));
}

inline static Word LBRNMIN(Word a,Word b)
{
  return LBRNCOMP(a,b) > 0 ? b : a;
}

inline static Word LBRNMAX(Word a,Word b)
{
  return LBRNCOMP(a,b) < 0 ? b : a;
}

/*************************************************************
 **  set_precis_faithfull: This function scales x and y equally.
 *************************************************************/
void Rend_Win::set_precis_faithfull()
{
  Word drx,dry,dvx,dvy,sx,sy,e,tmp,yp,xp,scale,k;

  /* dr stands for "rend window dimensions" */
  drx = RNINT(pixdim.x);
  dry = RNINT(pixdim.y);
  /* dv stands for "veiw windoe dimensions" */
  dvx = LBRNRN( LBRNDIF(X.W,x.W) );
  dvy = LBRNRN( LBRNDIF(Y.W,y.W) );
  /* We want drx / dvx = dry / dvy */
  sx = RNQ(drx,dvx);
  sy = RNQ(dry,dvy);

  /* determine scale and change dv so that that scaling
     maps at least the desired viewing region into the
     rend window.
  */
  if (RNCOMP( sx , sy ) < 0) {
    scale = sx;
    k = LBRNQORD( RNLBRN(dvx) , ILBRN(pixdim.x) );
    dvy = RNQ(dry , scale);
    e = LBRNFIE(1,k);
    tmp = RNSUM( dvy , LBRNRN(e) );
    dvy = SECOND(SSILRCRI(dvy,tmp));
    dvy = LBRNP2PROD( dvy , -1 );
    yp = LBRNP2PROD(LBRNSUM(Y.W,y.W),-1);
    y.W = LBRNDIF(yp,dvy);
    Y.W = LBRNSUM(yp,dvy); }
  else {
    scale = sy;
    k = LBRNQORD( RNLBRN(dvy) , ILBRN(pixdim.y) );
    dvx = RNQ(drx , scale);
    e = LBRNFIE(1,k);
    tmp = RNSUM( dvx , LBRNRN(e) );
    dvx = SECOND(SSILRCRI(dvx,tmp));
    dvx = LBRNP2PROD( dvx , -1 );
    xp = LBRNP2PROD(LBRNSUM(X.W,x.W),-1);
    x.W = LBRNDIF(xp,dvx);
    X.W = LBRNSUM(xp,dvx); }

  precis.x = precis.y = k-4; // The -4 is arbitrary it says something
  // about how close a point has to be to another pixel for a mistake
  // to be possible
}

void Rend_Win::update_extents(Rend_Cell &M)
{
  Word minx,maxx,miny,maxy,i,d;
  minx = LBRNMIN(M[0].sample -> coordinate(0),x.W);
  maxx = LBRNMAX(M[M.child.size()-1].sample -> coordinate(0),X.W);
  miny = LBRNMIN(M[1][0].sample -> coordinate(0),y.W);
  maxy = LBRNMAX(M[1][M[1].child.size()-1].sample -> coordinate(0),Y.W);

  d = LBRNDIF(maxy,miny); //-- arbitrary

  M.set_extents(LIST2(minx,maxx));
  miny = LBRNDIF(miny,d);
  maxy = LBRNSUM(maxy,d);
  for(i = 0; i < M.child.size(); i++)
    M[i].set_extents(LIST2(miny,maxy));
}



Word Rend_Win::map_x(Word b)
{
  Word t,r;
  t = LBRNPROD( LBRNDIF(b,x.W) , LBRNFIE(pixdim.x,0) );
  r = RNQ( LBRNRN(t) , LBRNRN( LBRNDIF(X.W,x.W) ) );
  r = RNFLOR(r);
  r = IMIN(r,100+pixdim.x);
  r = IMAX(r,-100);
  return r;
}

Word Rend_Win::map_y(Word b)
{
  Word t,r;
  t = LBRNPROD( LBRNDIF(b,y.W) , LBRNFIE(pixdim.y,0) );
  r = RNQ( LBRNRN(t) , LBRNRN( LBRNDIF(Y.W,y.W) ) );
  r = RNFLOR(r);
  r = IMIN(r,(Word)(1.5*pixdim.y));
  r = IMAX(r,(Word)(-0.5*pixdim.y));
  return r;
}

void Rend_Win::write_header(ostream &out)
{
  out << pixdim.x << "\t" << pixdim.y << endl << endl;
}

Word Rend_Win::get_lociva(Rend_Cell &M)
{
  Word i,L;
  for(i = 2; LBRNCOMP(M[i].sample->coordinate( precis.x ) ,
		      x.W) <= 0; i += 2);
  for(L=NIL; i < M.child.size() &&
	     LBRNCOMP(M[i].sample->coordinate( precis.x ) ,
		      X.W) < 0; i += 2) {
    L = COMP( i-1 , L ); }

  L = COMP(i-1,L);

  return L;
}


