/*===========================================================================
                       WRITE_PLOT(M,W,l,r,out)

Fill in the 2D sections over sectors.

Inputs
  M : The Rend_Cell cell structure for the CAD.
  W : The Rend_Win structure defining the viewing infromation.
  l : The index of the leftmost sector of M to bel plotted.
  r : The index of the rightmost sector of M to bel plotted.
  FIFO_Name : The name of the pipe to write to.
===========================================================================*/
#include "rend.h"
#include "Mapper.h"

void WRITE_PLOT(Rend_Cell &M, Rend_Win &W, Word l, Word r, ostream& out)
{
  Word i,j;

  Mapper Q(0,0,W.pixdim.x,W.pixdim.y,W);

  // Sectors over Sectors
  for(i = l; i <= r; i += 2) {
    M[i].out_descrip(W,out,Q);
    for( j = 1; j < M[i].child.size() - 1; j+=2) {
      M[i][j].out_descrip(W,out,Q); } }


  // Section and Cells over sections.
  for(i = l + 1; i < r; i += 2) {
    M[i].out_descrip(W,out,Q);
    for( j = 1; j < M[i].child.size() - 1; j++) {
      M[i][j].out_descrip(W,out,Q); } }
  

  // Sections over Sectors
  for(i = l; i <= r; i += 2) {
    for( j = 2; j < M[i].child.size() - 1; j+=2) {
      M[i][j].out_descrip(W,out,Q); } }
  
  out << 'F' << endl << flush; // Refresh SRGP.

  for(int i = 1024; i > 0; --i) out << ' ' << endl; out << flush;
  return;
}
