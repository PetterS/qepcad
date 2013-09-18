/*======================================================================
                 d <- SOLSETDIM(D,k)

Solution set dimension.

Inputs
  D  : a QEPCAD CAD
  k  : a BDigit, the dimension of the space in which this partial CAD
       is supposed to live.

Outputs
  d  : the dimension of the solution space (-1 if the space is empty!)
======================================================================*/
#include "qepcad.h"
#include <algorithm>
using namespace std;

BDigit SOLSETDIM(Word D, BDigit k)
{
  Word Lt, Lf, d = -1;

  LISTOFCWTV(D,&Lt,&Lf);
  for(Word L = Lt; L != NIL; L = RED(L))
  {
    Word cd = CELLDIM(FIRST(L));
    Word cl = LELTI(FIRST(L),LEVEL);
    d = max(d,cd + (k - cl));
  }

  return d;
}
