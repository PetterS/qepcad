/*======================================================================
                      Lp <- PTRRED(L)

Reductum 1. (assuming first element of L is a pointer)

Inputs
  L  : list of length 1 or more.

Outputs
  Lp  : the first reductum of L. (assuming 1st elt of L is a pointer)
======================================================================*/
#include "saclib.h"

Word PTRRED(L)
       Word L;
{
#if __WORDSIZE == 64
  return RED4(L);
#else /* Assumes 32-bit pointers. */
  return RED2(L);
#endif  
}
