/* Write a postscript plot of the CAD. */
#include "rend.h"
#include "Mapper.h"

void EPS_HEADER(double x1, double y1, double x2, double y2, double offset, ostream& out, double D)
{
  out << "%!PS-Adobe-2.0 EPSF-1.2" << endl;
  out << "%%BoundingBox: " << int(floor(x1 + D)) << " " << int(floor(y1 + D)) << " " 
      << int(ceil(x2 + 2*offset + D)) << " " << int(ceil(y2 + 2*offset + D)) << endl;
  out << "%%Creator: QEPCAD B Version " << QEPCADBVersion() << endl;
  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << endl;
  out << "%% The following moves plot to printable area for typical printer" 
      << endl;
  out << "gsave\n" << D << " " << D << " translate\n" << endl;
}

void cellcolors_m(ostream &out);
void cellcolors_c(ostream &out);

void WRITE_EPS(Rend_Cell &M, Rend_Win &W, Word L, Word e, Word P, ostream &out, bool c, bool z)
{
  Word l,r;
  
  /****************************************
  *** Initialize     
  *****************************************/
  l = LAST(L);
  r = FIRST(L);  
  Rend_Win Wp(W);

  /****************************************
  *** Write ps header
  *****************************************/
  double D = 20;
  double offset = 5;
  double x1 = 0, y1 = 0, x2 = 350, y2 = 350*double(W.pixdim.y)/W.pixdim.x,
    offsetp = offset * 1000 / double(350);

  out.setf(ios::showpoint);
  out << setprecision(4);

  EPS_HEADER(x1,y1,x2,y2,offset,out,D);

  if (c)
    cellcolors_c(out);
  else
    cellcolors_m(out);

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
  if (z)  { out << '%'; } out << "/DOT { pop pop } def" << endl;
  if (!z) { out << '%'; } out << "/DOT { newpath 5 0 360 arc stroke } def" << endl << endl;

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
}
  

void cellcolors_m(ostream &out)
{
  out << "%% This defines some default colors.\n"
      << "/DarkTrue { 0 setgray } def\n"
      << "/LightTrue { 0.85 setgray } def\n"
      << "/DarkFalse { 0.4 setgray } def\n"
      << "/LightFalse { 1 setgray } def\n" 
      << "/GridColor { 0.75 setgray } def\n"
      << "/AxisColor { 0.6 setgray } def\n" << endl;
}

void cellcolors_c(ostream &out)
{
  out << "%% This defines some default colors.\n"
      << "/DarkTrue { 0.2 0.4 1.0 setrgbcolor } def\n"
      << "/LightTrue { 0.2 1.0 1.0 setrgbcolor } def\n"
      << "/DarkFalse { 0.8667 0 0 setrgbcolor } def\n"
      << "/LightFalse { 0.8667 0.8667 0.8667 setrgbcolor } def\n" 
      << "/GridColor { 1 1 1 setrgbcolor } def\n"
      << "/AxisColor { 0 1 0 setrgbcolor } def\n" << endl;
}
