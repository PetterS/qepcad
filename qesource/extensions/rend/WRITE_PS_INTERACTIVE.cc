/* Write a postscript plot of the CAD. */
#include "rend.h"
#include "Mapper.h"
#include <map>
#include <string>
using namespace std;


//---------------------------------------------------------------//
//-- Takes QEPCAD cell C and int pair list p = (I,J) and returns
//-- true if and only if proj fac P_i,j is zero in C.
//-- D is the CAD, P is the p.f. set
//---------------------------------------------------------------//
Word XX(Word C, Word p, Word D, Word P)
{
  Word I,J,L,i,j;
  
  /* p is not a list (I,J) */
  if (!ISLIST(p) || LENGTH(p) < 2)
    return FALSE;
  FIRST2(p,&I,&J);

  /* Find (I,J) in the list of pf's zero in C. */
  for(L = LPFZCAL(D,C,P); L != NIL; L = RED(L)) {
    FIRST2(RED(LELTI(FIRST(L),PO_LABEL)),&i,&j);
    if (I == i && J == j)
      return TRUE;
  }
  return FALSE;
}

//---------------------------------------------------------------//
//-- check(t,C) returns true iff cell C satisfies conditions t --//
//---------------------------------------------------------------//
inline int check(char t,Rend_Cell &C, Word p, Word D, Word P)
{
  return
    (t == 'a' ||  (t == 't' && C.truth == TRUE) ||
     (t == 'f' && C.truth == FALSE) ||
     (t == 'u' && C.truth == UNDET) ||
     (t == 'p' && XX(C.QEPCAD_Cell,p,D,P))
     );
}

//---------------------------------------------------------------//
//-- returns the next non-whitespace character ----------------//
//---------------------------------------------------------------//
char nnws()
{
  char c;
  while (c = CREAD(),c == ' ' || c == '\n');
  return c;
}

//---------------------------------------------------------------//
//-- GetColor(out) gets color choice from user and writes rgb ---//
//---------------------------------------------------------------//
typedef map<string,int> CMT;
void GetColor(ostream &out)
{
  // Declare & initialize M //
  static CMT M;
  if (M.empty()) {
#include "COLOR.txt"    
  }

  do {
    // Read Color Name into string S//
    SWRITE("Color: ");
    char T[100];
    int i = 0;
    for(T[0] = nnws();T[++i] = CREAD(), T[i] != '\n';);
    for(T[i] = '\0';T[--i] == ' '; T[i] = '\0');
    string S(T);

    // Look for S in M //
    CMT::iterator p = M.find(S);
    if (p != M.end()) {
      out <<      (p->second >> 16) / 255.0 << " " 
	  << ((p->second >> 8) % 256) / 255.0 << " " 
	  <<      (p->second % 256) / 255.0 << " setrgbcolor" << endl;
      return;
    }
    SWRITE("Color not found!\n");
  }while(1);
}

//---------------------------------------------------------------//
//-- WRITE_PS_INTERACTIVE
//---------------------------------------------------------------//
void WRITE_PS_INTERACTIVE(Rend_Cell &M, Rend_Win &W, Word L, Word e, Word D, Word P)
{
  Word l,r;
  l = LAST(L);
  r = FIRST(L);
  
  /****************************************
  *** Get file name.
  *****************************************/
  string S;
  ofstream out;
  do {
    SWRITE("File name for postscript output? ");
    qein() >> S;
    out.open(S.c_str());
    if (out) break;
    cout << "File \"" << S << "\" could not be opened." << endl;
  } while (1);

  /****************************************
  *** Get x,y precision.
  *****************************************/
  Rend_Win Wp(W);
  {
    int x,y;
    SWRITE("Precision k (means precise to within 2^k) for x values: ");
    SWRITE("(Currently "); IWRITE(Wp.precis.x); SWRITE(") ");
    qein() >> x;
    SWRITE("Precision k (means precise to within 2^k) for y values: ");
    SWRITE("(Currently "); IWRITE(Wp.precis.y); SWRITE(") ");
    qein() >> y;
    SWRITE("\n");
    Wp.precis.x = min(x,Wp.precis.x);
    Wp.precis.y = min(y,Wp.precis.y);
  }
  if (Wp.precis.x < W.precis.x || Wp.precis.y < W.precis.y)
    FILL_2D(M,Wp,e,L,P);
  
  
  /****************************************
   *** Write ps header
   *****************************************/
  double offset = 5;
  double x1 = 0, y1 = 0, x2 = 350, y2 = 350*double(W.pixdim.y)/W.pixdim.x,
    offsetp = offset * 1000 / double(350);
  
  out.setf(ios::showpoint);
  out << setprecision(4);


  EPS_HEADER(x1,y1,x2,y2,offset,out,20);


  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "/VERT { newpath dup " << -offsetp << " moveto " 
      << 1000 + offsetp << " lineto stroke } def" << endl;
  out << "/HORZ { newpath dup " << -offsetp << " exch moveto " 
      << 1000 + offsetp << " exch lineto stroke } def" << endl;

  out << "gsave\n" << offset << " " << offset << " translate\n" << endl;

  out << endl 
      << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl
      << "%% Here I'm scaling so that a 1000 x 1000 box fits the Bounding Box.\n"
      << x2/1000 << " " << y2/1000 << " scale\n"
      << "%% From now on, everything takes place in a 1000 x 1000 box!\n"
      << endl;

  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Here I'm setting to clip to the bounding box!"
      << "\ngsave\nnewpath\n" 
      << 0 << " " << 0 << " moveto\n"
      << 0 << " " << 1000 << " lineto\n"
      << 1000 << " " << 1000 << " lineto\n"
      << 1000 << " " << 0 << " lineto\n"
      << "closepath\nclip\n"
      << "%% From now on, nothing is allowed outside the 1000 x 1000 box!\n"
      << endl;

  out << "/TC { } def" << endl <<  "/FC { } def" << endl << "/UC { } def" << endl;
   
  Mapper Q(0,0,1000,1000,Wp);
  Word i,j;


  for(int f = 1; f; ) {
    /* Get Command. */
    SWRITE("\nEnter command [q:quit, g:gridlines, a:axes, c:cells]: ");
    char c;
    c = nnws();
    switch(c) {

      /**********************************************************
       ** QUIT								 
       **********************************************************/
    case 'q': f = 0; break;

      /**********************************************************
       ** Axes
       **********************************************************/
    case 'a':
      {
	Word OX, OY,xoff,yoff;
	double dum,Ox = 0, Oy = 0;
	SWRITE("Provide an origin: ");
	qein() >> Ox >> Oy;
	OX = IEEELBRN(Ox);
	OY = IEEELBRN(Oy);
	if (LBRNCOMP(OX,W.x.W) < 0 || LBRNCOMP(OX,W.X.W) > 0 ||
	    LBRNCOMP(OY,W.y.W) < 0 || LBRNCOMP(OY,W.Y.W) > 0 )
	  SWRITE("Origin not in view! Axes not plotted!\n");
	else {
	  out << "%% AXES %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	  GetColor(out);
	  Q.Xwrite(OX,out,8); out << " VERT" << endl;
	  Q.Ywrite(OY,out,8); out << " HORZ" << endl;
	}
      }
	break;

      /**********************************************************
       ** Gridlines
       **********************************************************/
    case 'g':
      {
	Word OX, OY,xoff,yoff;
	double dum,Ox = 0, Oy = 0;
	SWRITE("Provide an origin: ");
	qein() >> Ox >> Oy;
	OX = IEEELBRN(Ox);
	OY = IEEELBRN(Oy);
	SWRITE("x offset : ");
	SWRITE("y offset : ");
	qein() >> dum;
	xoff = IEEELBRN(dum);
	qein() >> dum;
	yoff = IEEELBRN(dum);
	out << "%% GRIDLINES %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	GetColor(out);
	Word tw;
	for(tw = OX; LBRNCOMP(tw,W.X.W) < 0; tw = LBRNSUM(tw,xoff)) {
	  Q.Xwrite(tw,out,8); out << " VERT" << endl; }
	for(tw = LBRNDIF(OX,xoff); LBRNCOMP(tw,W.x.W) > 0; tw = LBRNDIF(tw,xoff)) {
	  Q.Xwrite(tw,out,8); out << " VERT" << endl; }
	for(tw = OY; LBRNCOMP(tw,W.Y.W) < 0; tw = LBRNSUM(tw,yoff)) {
	  Q.Ywrite(tw,out,8); out << " HORZ" << endl; }
	for(tw = LBRNDIF(OY,yoff); LBRNCOMP(tw,W.y.W) > 0; tw = LBRNDIF(tw,yoff)) {
	  Q.Ywrite(tw,out,8); out << " HORZ" << endl; }      
      }
      break;
	
      /**********************************************************
       ** Cells
       **********************************************************/
    case 'c':
      SWRITE("Which cells: a -- sections over sections\n");
      SWRITE("             b -- sections over sectors\n");
      SWRITE("             c -- sectors over sections\n");
      SWRITE("             d -- sectors over sectors\n");
      SWRITE("?: ");
      c = nnws();
      if (c != 'a' && c != 'b' && c != 'c' && c != 'd') {
	SWRITE("Bad choice!\n"); break; }
      char t;
      SWRITE("True, false, undet, all, or polynomial? (t|f|u|a,p): ");
      t = nnws();
      if (t != 't' && t != 'f' && t != 'u' && t != 'a' && t != 'p') {
	SWRITE("Bad choice!\n"); break; }
      
      // Formula case
      Word p;
      if (t == 'p') {
	  SWRITE("Enter projetion factor by (level,index): ");
	  p = LREAD(); }

      switch(c) {
      case 'x': // 1D Sectors
	out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	out << "%% Begin cell-type D1_1 %%%%%%%%%%%%%%%%%%%%%%%" << endl;
	out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	for(i = l; i <= r; i += 2)
	  if (M[i].child.size() == 2)
	    M[i].out_descrip_ps_standard(Wp,out,Q);
	break;
	
      case 'd': // Sectors over sectors
	out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	out << "%% Begin cell-type D2_11 %%%%%%%%%%%%%%%%%%%%%%" << endl;
	out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	GetColor(out);
	for(i = l; i <= r; i += 2)
	  for(j = 1; j < M[i].child.size(); j += 2)
	    if (M[i].child.size() > 2 && check(t,M[i][j],p,D,P))     
	      M[i][j].out_descrip_ps_standard(Wp,out,Q);
	break;
	
      case 'c': // Sectors over sections 
	out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	out << "%% Begin cell-type D2_01 %%%%%%%%%%%%%%%%%%%%%%" << endl;
	out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	GetColor(out);
	for(i = l + 1; i < r; i += 2)
	  for(j = 1; j < M[i].child.size(); j += 2)
	    if (M[i].child.size() > 2 && check(t,M[i][j],p,D,P))
	      M[i][j].out_descrip_ps_standard(Wp,out,Q);
	break;
	

      case 'b': // Sections over sectors
	out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	out << "%% Begin cell-type D2_10 %%%%%%%%%%%%%%%%%%%%%%" << endl;
	out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	GetColor(out);
	for(i = l; i <= r; i += 2)
	  for(j = 2; j < M[i].child.size() - 1; j += 2)
	    if (M[i].child.size() > 2 && check(t,M[i][j],p,D,P))
	      M[i][j].out_descrip_ps_standard(Wp,out,Q);
	break;

      case 'a': // Sections over sections
	out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	out << "%% Begin cell-type D2_00 %%%%%%%%%%%%%%%%%%%%%%" << endl;
	out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	GetColor(out);
	out << "/DOT { newpath 50 0 360 arc stroke } def" << endl << endl;
	for(i = l + 1; i < r; i += 2)
	  for(j = 2; j < M[i].child.size() - 1; j += 2)
	    if (M[i].child.size() > 2 && check(t,M[i][j],p,D,P))
	      M[i][j].out_descrip_ps_standard(Wp,out,Q);
	break;
      }

      break;

    }
  }

  /****************************************
  *** Footer
  *****************************************/  
  out << "\ngrestore % Restore after the bounding box clip!\n";
  
  out << "%% Here I'm drawing a box around the plot!"
      << "\nnewpath\n" 
      << 0 << " " << 0 << " moveto\n"
      << 0 << " " << 1000 << " lineto\n"
      << 1000 << " " << 1000 << " lineto\n"
      << 1000 << " " << 0 << " lineto\n"
      << "closepath\nstroke\n"
      << endl;
  
  
  out << "\ngrestore % Restore after the translation and scaling!\n";
  out << "\ngrestore % Restore after move to printable area!\n";
  out << "showpage" << endl;
  out.close();
}

