/*======================================================================
                 DISP2DCAD(D,P,J)

Inputs
  D : a CAD data-structure
  P : the projection factor set for D
  J : the projection polynomial set for D

Side Effects
First, this reads in arguments for plotting, the character D indicates
that default values are to be used for all parameters, while E indicates
that the user will type in explicit values.  The 2D CAD plotting 
programs are then called.
======================================================================*/
#include "rend.h"

void QepcadCls::DISP2DCAD(Word D, Word P, Word J)
{
  char c;

  // Get character determining default vs. explicit
  if (!(qein() >> c) || (c != 'E' && c != 'D') ) { 
    SWRITE("D or E expected!\n"); return; }
  if (c == 'D') {
    // Default arguments
    PLOT_2D_CAD(D,P,J,0,0,0,0,0,400,400,*this); }
  else if (c == 'E') {
    //Explicit arguments
    double x,X,y,Y,e;
    int wx,wy;
    if (!(singlelinestream(qein(),singlelinestream::skipleadingws) >> x >> X >> y >> Y >> wx >> wy >> e))
      SWRITE("7 numeric arguments expected, try 'whatis d-2d-cad'!\n");
    else {
      PLOT_2D_CAD(D,P,J,IEEELBRN(x),IEEELBRN(X),IEEELBRN(y),
		  IEEELBRN(Y),IEEELBRN(e),wx,wy,*this); } }

  return;
}

