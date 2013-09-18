/*======================================================================
                      L <- ADJ_2D(c,c_l,c_r,P,J)

Adjacency for 2D CAD cells.

Inputs
  c  : a section cell in the 1D CAD.
  c_l: c's left neighbor.
  c_r: c's right neighbor.
  P  : the projection factor set.
  J  : the projection polynomial set.

Outputs
  L  : a list of elements of the form ((i,j),(k,l))
       indicating an adjacency between cell (i,j) and cell (k,l).
       Returns AD2D_FAIL if it fails.
======================================================================*/
#include "adj2D.h"
#include "adj2D.h"
static void start();
static void stop();
static int k;
static void zero() { k = 0; }
void bump() { k++; }
static void print() { SWRITE("\n\nk = "); IWRITE(k); SWRITE("\n\n"); }

Word ADJ_2D(Word c, Word c_l, Word c_r, Word P, Word J)
{
  Word U,V,W,v_l,Sol;

  v_l = LDCOEFMASK(c,P,J);
  U = AD2DS_CONS(c_l,P);
  V = AD2DS_CONS(c,P);
  W = AD2DS_CONS(c_r,P);

  Sol = P3(U,V,W,v_l,FIRST(LELTI(c,INDX)));

  return Sol;
}

static Word ADJ_D_Time;

void start()
{
  ADJ_D_Time = ACLOCK();
}

void stop()
{
  ADJ_D_Time = ACLOCK() - ADJ_D_Time;
  SWRITE("\nADJ_2D took ");
  IWRITE(ADJ_D_Time);
  SWRITE(" millseconds.\n");
}
