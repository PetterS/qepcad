/*======================================================================
                      PLOT2DCAD2FILE(D,P,J)

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

void QepcadCls::PLOT2DCAD2FILE(Word D, Word P, Word J)
{

/********************************************************************/
Step0: /* Read user input */

  // Get basic info
  double x,X,y,Y,e;
  int Id1 = 200, Id2 = 200;
  char S[40];
  singlelinestream lin(qein(),singlelinestream::skipleadingws);
  if (!(lin >> x >> X >> y >> Y >> e >> S)) {
    SWRITE("xmin xmax ymin ymax stride filename, try 'whatis d-2d-cad'!\n");
    qein().putback('\n'); //QEPCAD's next command function looks for a newline first!
    return; }
  if (!( x < X && y < Y)) {
    SWRITE("Must have xin < xmax, ymin < ymax!\n");
    qein().putback('\n'); //QEPCAD's next command function looks for a newline first!
    return; }

  // Get additional flags
  bool 
    z = true, // show zero dimensional cell
    c = true; // make a plot in color
  char g;
  while((g = lin.get()) && g != EOF) {
    switch(g) {
    case 'z': z = false; break;
    case 'Z': z = true; break;
    case 'c': c = false; break;
    case 'C': c = true; break;
    default: break;
    } }
  qein().putback('\n'); //QEPCAD's next command function looks for a newline first!

/********************************************************************/
Step1: /* Make sure at least the CAD of 1-space exists. Initialize. */
      if (LELTI(D,CHILD) == NIL) {
	SWRITE("No decomposition to plot!\n");
	return; }

/********************************************************************/
 Step2: /* Open the output file. */
  ofstream out;
  out.open(S);
  if (!out) {
    printf("File %s could not be opened.\n",S);
    return; }

/********************************************************************/
Step3:/* Get a nice initial plot.                                   */
  Word Ix = IEEELBRN(x),IX = IEEELBRN(X),Iy = IEEELBRN(y),
    IY = IEEELBRN(Y),E = IEEELBRN(e),L;
  Rend_Cell M;        /* M is the "mirror" CAD for plotting.    */
  CONMIRCAD(D,P,J,M,*this); /* This actually constructs M.            */
  Rend_Win W(M,Id1,Id2,Ix,IX,Iy,IY);
  W.update_extents(M);
  L = W.get_lociva(M);
  FILL_2D(M,W,E,L,P);
  
/********************************************************************/
Step4: /* Produce plot! */  
  WRITE_EPS(M,W,L,E,P,out,c,z);
  out.close();

  return;
}

