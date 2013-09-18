/********************
Display from coordinates.
*********************/

#include "qepcad.h"

void DISPFC2DCAD(Word D, Word P, Word J)
{
  Word x,X,y,Y,e,d1,d2;
  if (get_coords__FPiN60(&x,&X,&y,&Y,&e,&d1,&d2)) {
    I've still got to convert the floats to binary rationals.
    PLOT_2D_CAD__Fiiiiiiiiii(D,P,J,x,X,y,Y,e, d1,d2); }
  else {
    SWRITE("7 parameters are expected: floating point values\n");
    SWRITE("for the lower and upper x-values of the viewing box,\n");
    SWRITE("floating point values for the lower and upper y\n");
    SWRITE("values of the viewing box, a binary rational offset\n");
    SWRITE("for plotting points, an integer pixel width for the\n");
    SWRITE("plot window, and an integer pixel height for the\n");
    SWRITE("plot window\n\n"); }
      
  return;
}


