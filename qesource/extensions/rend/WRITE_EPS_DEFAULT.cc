/* Write a postscript plot of the CAD. */
#include "rend.h"
#include "Mapper.h"


void defaultcolordefs(ostream &out)
{
  out << "%% Color def's\n" 
      << "/TSN {0.0 0.0 1.0 setrgbcolor} def" << endl
      << "/TSR {0.678 0.847 0.901 setrgbcolor} def" << endl
      << "/FSN {0.647 0.165 0.165 setrgbcolor} def" << endl
      << "/FSR {1.0 0.98 0.804 setrgbcolor} def" << endl;
}

void defaultmonochromedefs(ostream &out)
{
  out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% This defines some default colors.\n"
      << "/DarkTrue { 0 setgray } def\n"
      << "/LightTrue { 0.85 setgray } def\n"
      << "/DarkFalse { 0.4 setgray } def\n"
      << "/LightFalse { 1 setgray } def\n" 
      << "/GridColor { 0.75 setgray } def\n"
      << "/AxisColor { 0.6 setgray } def\n" << endl;
}
void WRITE_EPS_DEFAULT(Rend_Cell &M, Rend_Win &W, Word L, Word e, Word P, ostream &out)
{
  Word l,r;
  l = LAST(L);
  r = FIRST(L);

  /****************************************
  *** Get x,y precision.
  *****************************************/
  Rend_Win Wp(W);

 
   /****************************************
  *** Write ps header
  *****************************************/
  double x1 = 0, y1 = 0, x2 = 350, y2 = 350*double(W.pixdim.y)/W.pixdim.x;

  out.setf(ios::showpoint);
  out << setprecision(4);

  EPS_HEADER(x1,y1,x2,y2,0,out);

  out << endl 
      << "%% Here I'm scaling so that a 1000 x 1000 box fits the Bounding Box.\n"
      << x2/1000 << " " << y2/1000 << " scale\n"
      << "%% From now on, everything takes place in a 1000 x 1000 box!\n"
      << endl;

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
  for(i = l; i <= r; i += 2)
    M[i].out_descrip_ps_color(Wp,out,Q);

  // Sectors over sectors
  for(i = l; i <= r; i += 2)
    for(j = 1; j < M[i].child.size(); j += 2)
      M[i][j].out_descrip_ps_color(Wp,out,Q);

  // 1D Sections
  for(i = l + 1; i < r; i += 2)
    M[i].out_descrip_ps_color(Wp,out,Q);

  // Sections over sectors
  for(i = l; i <= r; i += 2)
    for(j = 2; j < M[i].child.size() - 1; j += 2)
      M[i][j].out_descrip_ps_color(Wp,out,Q);

  // Sections & Sectors over sections
  for(i = l + 1; i < r; i += 2)
    for(j = 1; j < M[i].child.size(); j ++)
      M[i][j].out_descrip_ps_color(Wp,out,Q);

  
  out << "\ngrestore % Restore after the bounding box clip!\n";
  out << "showpage" << endl;
}
  
