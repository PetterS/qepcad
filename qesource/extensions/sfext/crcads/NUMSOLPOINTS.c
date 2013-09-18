/*======================================================================
                 n <- NUMSOLPOINTS(Word D, BDigit k)

Number of solution points.

Inputs
  D  : a QEPCAD CAD
  k  : a BDigit, the dimension of the space in which this partial CAD
       is supposed to live.

Outputs
  n  : the number of solution points (-1 if not finite!)
======================================================================*/
#include "qepcad.h"

BDigit NUMSOLPOINTS(Word D, BDigit k)
{
  Word Lt, Lf, n = -1;
  
  if (SOLSETDIM(D,k) <= 0)
  {
    LISTOFCWTV(D,&Lt,&Lf);
    n = LENGTH(Lt);
  }

  return n;
}
