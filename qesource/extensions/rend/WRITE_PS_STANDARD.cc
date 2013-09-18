/* Write a postscript plot of the CAD. */
#include "rend.h"
#include "Mapper.h"


void WRITE_PS_STANDARD(Rend_Cell &M, Rend_Win &W, Word L, Word e, Word P, Word Oflag)
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

  Word OX, OY,xoff,yoff;
  if (Oflag) {
    double Ox = 0, Oy = 0,dum;
    SWRITE("Provide an origin: ");
    qein() >> Ox >> Oy;
    OX = IEEELBRN(Ox);
    OY = IEEELBRN(Oy);
    if (LBRNCOMP(OX,W.x.W) < 0 || LBRNCOMP(OX,W.X.W) > 0 ||
	LBRNCOMP(OY,W.y.W) < 0 || LBRNCOMP(OY,W.Y.W) > 0 ) {
      SWRITE("Origin not in view!\n");
      Oflag = 0; }
    else {
      SWRITE("x offset : ");
      SWRITE("y offset : ");
      qein() >> dum;
      xoff = IEEELBRN(dum);
      qein() >> dum;
      yoff = IEEELBRN(dum); } }
 
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
  out << "%% This defines some default colors.\n"
      << "/DarkTrue { 0 setgray } def\n"
      << "/LightTrue { 0.85 setgray } def\n"
      << "/DarkFalse { 0.4 setgray } def\n"
      << "/LightFalse { 1 setgray } def\n" 
      << "/GridColor { 0.75 setgray } def\n"
      << "/AxisColor { 0.6 setgray } def\n" << endl;

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
  out << "%% This defines action for single point cells. " << endl;
  out << "/DOT { pop pop } def" << endl;
  out << "%/DOT { newpath 5 0 360 arc stroke } def" << endl << endl;

   /****************************************
  *** Section 1: Full-dimensional cells
  *****************************************/

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
   
  Mapper Q(0,0,1000,1000,Wp);
  Word i,j;
   
  // 1D Sectors
  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Begin cell-type D1_1 %%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Color def's\n" 
      << "/TC {LightTrue} def" << endl
      << "/FC {LightFalse} def" << endl
      << "/UC {0.0 0.98 0.804 setrgbcolor} def" << endl;
  for(i = l; i <= r; i += 2)
    if (M[i].child.size() == 2)
      M[i].out_descrip_ps_standard(Wp,out,Q);

  // Sectors over sectors
  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Begin cell-type D2_11 %%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Color def's\n" 
      << "/TC {LightTrue} def" << endl
      << "/FC {LightFalse} def" << endl
      << "/UC {0.0 0.98 0.804 setrgbcolor} def" << endl;
  for(i = l; i <= r; i += 2)
    for(j = 1; j < M[i].child.size(); j += 2)
      if (M[i].child.size() > 2)
	M[i][j].out_descrip_ps_standard(Wp,out,Q);

  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Here I'm drawing outside the bounding box!" << endl;
  out << "grestore\n" << endl;

   /****************************************
  *** Section 2: Between stuff
  *****************************************/

if (Oflag) {
  out << "gsave\n";
  out << "AxisColor" << endl;
  Q.Xwrite(OX,out,8); out << " VERT" << endl;
  Q.Ywrite(OY,out,8); out << " HORZ" << endl;

  out << "GridColor" << endl;
  Word tw;
  for(tw = LBRNSUM(OX,xoff); LBRNCOMP(tw,W.X.W) < 0; tw = LBRNSUM(tw,xoff)) {
    Q.Xwrite(tw,out,8); out << " VERT" << endl; }
  for(tw = LBRNDIF(OX,xoff); LBRNCOMP(tw,W.x.W) > 0; tw = LBRNDIF(tw,xoff)) {
    Q.Xwrite(tw,out,8); out << " VERT" << endl; }

  for(tw = LBRNSUM(OY,yoff); LBRNCOMP(tw,W.Y.W) < 0; tw = LBRNSUM(tw,yoff)) {
    Q.Ywrite(tw,out,8); out << " HORZ" << endl; }
  for(tw = LBRNDIF(OY,yoff); LBRNCOMP(tw,W.y.W) > 0; tw = LBRNDIF(tw,yoff)) {
    Q.Ywrite(tw,out,8); out << " HORZ" << endl; }
    

  out << "grestore\n" << endl;
}


   /****************************************
  *** Section 2: 1 and 0 dimensional cells
  *****************************************/

  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Here I'm setting to clip to the bounding box ... again"
      << "\ngsave\nnewpath\n" 
      << 0 << " " << 0 << " moveto\n"
      << 0 << " " << 1000 << " lineto\n"
      << 1000 << " " << 1000 << " lineto\n"
      << 1000 << " " << 0 << " lineto\n"
      << "closepath\nclip\n"
      << "%% From now on, nothing is allowed outside the 1000 x 1000 box!\n"
      << endl;
   


  // 1D Sections
  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Begin cell-type D1_0 %%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Color def's\n" 
      << "/TC {DarkTrue} def" << endl
      << "/FC {DarkFalse} def" << endl
      << "/UC {0.0 0.98 0.804 setrgbcolor} def" << endl;
  for(i = l + 1; i < r; i += 2)
    if (M[i].child.size() == 2)
      M[i].out_descrip_ps_standard(Wp,out,Q);

  // Sectors over sections
  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Begin cell-type D2_01 %%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Color def's\n" 
      << "/TC {DarkTrue} def" << endl
      << "/FC {DarkFalse} def" << endl
      << "/UC {0.0 0.98 0.804 setrgbcolor} def" << endl;
  for(i = l + 1; i < r; i += 2)
    for(j = 1; j < M[i].child.size(); j += 2)
      if (M[i].child.size() > 2)
	M[i][j].out_descrip_ps_standard(Wp,out,Q);

  // Sections over sectors
  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Begin cell-type D2_10 %%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Color def's\n" 
      << "/TC {DarkTrue} def" << endl
      << "/FC {DarkFalse} def" << endl
      << "/UC {0.0 0.98 0.804 setrgbcolor} def" << endl;
  for(i = l; i <= r; i += 2)
    for(j = 2; j < M[i].child.size() - 1; j += 2)
      if (M[i].child.size() > 2)
	M[i][j].out_descrip_ps_standard(Wp,out,Q);

  // Sections over sections
  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Begin cell-type D2_00 %%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Color def's\n" 
      << "/TC {DarkTrue} def" << endl
      << "/FC {DarkFalse} def" << endl
      << "/UC {0.0 0.98 0.804 setrgbcolor} def" << endl;
  for(i = l + 1; i < r; i += 2)
    for(j = 2; j < M[i].child.size() - 1; j += 2)
      if (M[i].child.size() > 2)
	M[i][j].out_descrip_ps_standard(Wp,out,Q);


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
  
