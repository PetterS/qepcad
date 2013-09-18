/*************************************************************
 **
 **  rend.h
 **
 **
 *************************************************************/
#ifndef _REND_
#define _REND_


class Rend_Cell;
class Rend_Sample;
class Rend_Win;

/*************************************************************
 **  Includes
 *************************************************************/
extern "C" {
#include <stdio.h>
};

/* adj2D needs to enclose adj2D.h in extern C, if qepcad is not all C++! */
//extern "C" {
#include <stdio.h>
#include "adj2D.h"
//};

#include <fstream>
#include "Safe_Array.h"
#include "gcmemloc.h"
#include "Rend_Sample.h"
#include "Rend_Cell.h"
#include "Rend_Win.h"

#include <iostream>
#include <sstream>
istream& qein(); // fetches the current qepcad istream object

class singlelinestream : public istringstream
{
public:
  enum option {none = 0, skipleadingws = 1};
  singlelinestream(istream& in, option opt = none)
  {
    string s = "";
    char c = in.get(); if (opt == skipleadingws) while(c != EOF && isspace(c)) c = in.get();
    while(c != '\n' && c != EOF) { s += c; c = in.get(); }
    str(s);
  }
};

/*************************************************************
 **  Function Prototypes
 *************************************************************/
Word LBRNQORD(Word A,Word B);
Word SSILRCRI(Word a_,Word b_);

void CONMIRCAD(Word D,Word P,Word J,Rend_Cell& M,QepcadCls &Q);
void ADD_POINTS( Rend_Cell &C, Word p_index, Word x, Word L_);
void FILL_2D( Rend_Cell &M, Rend_Win &W, Word e, Word L, Word P );
void WRITE_PLOT(Rend_Cell &M, Rend_Win &W, Word l, Word r, ostream &out);
Word ZOOM_OUT(Rend_Cell &M, Rend_Win &W, Word xf,
	      Word yf, Word N, Word P);
Word CH_VIEW_WIN(Rend_Cell &M, Rend_Win &W, Word Xs, Word Xt,
	      Word Ys,Word Yt, Word e, Word P);
Word CH_VIEW_WIN_COOR(Rend_Cell &M, Rend_Win &W, Word P, Word N,
		 Word x,Word X, Word y, Word Y);
void WRITE_PS(Rend_Cell &M, Rend_Win &W, Word L, Word e, Word P);
void WRITE_PS_COLOR(Rend_Cell &M, Rend_Win &W, Word L, Word e, Word P);
void WRITE_PS_STANDARD(Rend_Cell &M, Rend_Win &W, Word L, Word e, Word P, Word Oflag = 0);
void WRITE_PS_RAJI(Rend_Cell &M, Rend_Win &W, Word L, Word e, Word P, Word Oflag = 1);
void WRITE_PS_INTERACTIVE(Rend_Cell &M, Rend_Win &W, Word L, Word e, Word D, Word P);
void WRITE_EPS(Rend_Cell &M, Rend_Win &W, Word L, Word e, Word P,ostream& out, bool c, bool z);

void PLOT_2D_CAD(Word D, Word P, Word J, 
		 Word Ix, Word IX, Word Iy, Word IY, Word e,
		 Word Id1, Word Id2, QepcadCls &QC);

void PLOTeps_2D_CAD(Word D, Word P, Word J, 
		    Word Ix, Word IX, Word Iy, Word IY, Word e, 
		    ostream &out, char cflag, char zdcell, QepcadCls &QC
);

void EPS_HEADER(double x1, double y1, double x2, double y2, double offset, ostream& out, double D = 0);

static inline int min(int a, int b) { return a < b ? a : b; }

#endif /* _REND_ */
