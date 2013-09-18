/*===========================================================================
                       PLOT_2D_CAD(D,P,J,Ix,IX,Iy,IY,e,Id1,Id2)

Plot 2-dimensional CAD

Inputs
  D : a CAD data-structure
  P : the projection factor set for D
  J : the projection polynomial set for D
  Ix:
  IX: (Ix,IX) the range of x-values to appear in the plot.
  Iy:
  IY: (Iy,IY) the range of y-values to appear in the plot.
  e : the distance between "samples"
  Id1:
  Id2: The plot window is Id1 x Id2 pixels.
===========================================================================*/
extern "C" {
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
	   }
#include <cstring>
#include <string>
#include <fstream>
#include <cmath>
#include "rend.h"
#include "../../source/db/unnamedpipe.h"
static void longtostring(long A, char* S);

/*###################################################################
  ###
  ### PLOT_2D_CAD
  ###
  ###################################################################*/
void PLOT_2D_CAD(Word D, Word P, Word J, 
		 Word Ix, Word IX, Word Iy, Word IY, Word e,
		 Word Id1, Word Id2, QepcadCls &QC)
{
      char c;
      Word N;
      Word i,j,I,ap,bp,a,b,L,p_n,n,A,Q,x,yl,Xs,Ys,Xt,Yt;
      char FIFO_NAME[20] =  "/tmp/_plot_pipe_",
	RM_FIFO[25] = "rm ";
      longtostring(getpid(),FIFO_NAME+11);
      int t = 1, first = 1;
      int wcount = 0;
      UnnamedPipe *pipePtr = NULL;
      
/********************************************************************/
Step1: /* Make sure at least the CAD of 1-space exists. Initialize. */
      if (LELTI(D,CHILD) == NIL) {
	SWRITE("No decomposition to plot!\n");
	return; }

/********************************************************************/
Step2:/* Get a nice initial plot.                                   */
      Rend_Cell M;        /* M is the "mirror" CAD for plotting.    */
      CONMIRCAD(D,P,J,M,QC); /* This actually constructs M.            */
      Rend_Win W(M,Id1,Id2,Ix,IX,Iy,IY);
      if (Ix == IX) {
	W.set_precis_faithfull();
	N = 10;
	e = LBRNP2PROD(LBRNDIF(W.X.W,W.x.W),-ILOG2(N)); }
      else {
	N = 10;
      }
      W.update_extents(M);
      L = W.get_lociva(M);
      FILL_2D(M,W,e,L,P);

/********************************************************************/
Step3: /* Write it. */
      if (t == 1) {
	t = 0;
	wcount++;
	if (!first) {
	  first = 0;
	  pipePtr->out() << "E" << endl;
	  delete pipePtr;
	  pipePtr = NULL; }
	else
	  first = 0;

	// Make the fifo.
	pipePtr = new UnnamedPipe;
	
	char* qe = getenv("qe");
	char call_plot[200];
	strcpy(call_plot,qe);
	strcpy(call_plot + strlen(call_plot),"/bin/ADJ2D_plot");
	
	// Call the plotting program.
	if (fork() == 0) {
	  //close(pipePtr->fdout());
	  pipePtr->closeOut();
	  dup2(pipePtr->fdin(),0);
	  if (execlp(call_plot,call_plot,NULL) < 0) {
	    cerr << "Didn't successfully execl for plot." << endl;
	    exit(1); } }
	
	pipePtr->closeIn();
	W.write_header(pipePtr->out()); }
      
      WRITE_PLOT(M,W, LAST(L), FIRST(L) , pipePtr->out());
      
/********************************************************************/
Step4: /* Write out info about current plot. */
      cout << endl;
      SWRITE("Window shows ");
      LBRIWRITE(LIST2(W.x.W,W.X.W));
      SWRITE(" x ");
      LBRIWRITE(LIST2(W.y.W,W.Y.W)); 
      SWRITE(".\nI.e. window shows ");
      LBRIDWRITE(LIST2(W.x.W,W.X.W),6);
      SWRITE(" x ");
      LBRIDWRITE(LIST2(W.y.W,W.Y.W),6);
      SWRITE(".\n\n");
  
/********************************************************************/
Step5: /* Get command. */
 comm_loop:
      cout << "Num. Points (n), View Win. Coords (c), Print Postscript (p)" << endl
	   << "New Plot Win (w), Quit (q)" << endl
	   << ": " << flush;
      if (qein() >> c) {
	switch(c) {
	case 's' :
	  cout << "2 binary rational translation values please: ";
	  Xt = LBRNREAD(); Yt = LBRNREAD();
	  cout << "2 binary rational scale factors please: ";
	  Xs = LBRNREAD(); Ys = LBRNREAD();
	  e = CH_VIEW_WIN(M,W,Xs,Xt,Ys,Yt,e,P);
	  L = W.get_lociva(M);
	  goto Step3;
	case 'n' :
	  SWRITE("How many evaluation points?\n");
	  N = IREAD();
	  e = LBRNP2PROD(LBRNDIF(W.X.W,W.x.W),-ILOG2(N));
	  L = W.get_lociva(M);
	  FILL_2D(M,W,e,L,P);
	  goto Step3;
	case 'w' :
	  t = 1;
	  goto Step3;
	case 'c':
	  {
	    double fx,fX,fy,fY;
	    Word z1,z2,z3,z4;
	    cout << "Input 4 floating point values, the minimum and" 
		 << "maximum x-values \nfollowed by the minimum and maximum"
		 << "y-values. \n(i.e. xmin xmax ymin ymax, where "
		 << "xmin < xmax and ymin < ymax)." << endl;
	    if (!(singlelinestream(qein(),singlelinestream::skipleadingws) >> fx >> fX >> fy >> fY)) {
	      cout << "Need 4 floating-point values!" << endl;
	      goto comm_loop; }
	    if (fx >= fX || fy >= fY) {
	      cout << "Must have: xmin < xmax and ymin < ymax!" << endl;
	      goto comm_loop; }
	    FIRST2( LIST2(IEEELBRN(fx),IEEELBRN(fX)), &z1, &z2);
	    FIRST2( LIST2(IEEELBRN(fy),IEEELBRN(fY)), &z3, &z4);
	    e = CH_VIEW_WIN_COOR(M,W,P,N,z1,z2,z3,z4);
	    L = W.get_lociva(M);
	    FILL_2D(M,W,e,L,P);
	    goto Step3;
	  }
	case 'q': 
	case 'Q':
	  goto Return;
	case 'p': /************ Postscript **************/
	  WRITE_PS(M,W,L,e,P);
	  goto comm_loop;  
	case 'e': /************ Postscript Color **************/
	  WRITE_PS_STANDARD(M,W,L,e,P,1);
	  goto comm_loop;  
	case 'r': /************ Postscript Color **************/
	  WRITE_PS_RAJI(M,W,L,e,P);
	  goto comm_loop;  
	case 'i': /************ Postscript Color **************/
	  WRITE_PS_INTERACTIVE(M,W,L,e,D,P);
	  goto comm_loop;  
	default :
	  cout << "Didn't recognize command!" << endl;
	  goto comm_loop;
	} }
      else
	goto Return;
  
/********************************************************************/
Return: /* Clean up and return. */
      if (pipePtr != NULL)
      {
	pipePtr->out() << 'E';
	delete pipePtr;
      }
      return;
}

/********************************************************************/
/** The stdlib function didn't quite work the way I wanted. *********/
/********************************************************************/
static void longtostring(long A, char* S)
{
  int i;
  for(i = 0; A != 0; A /= 10, i++)
    S[i] = ((A % 10) + '0');
  if (i == 0)
    S[i++] = '0';
  S[i] = '\0';
}

