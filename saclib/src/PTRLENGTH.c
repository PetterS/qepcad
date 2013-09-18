/*======================================================================
                      n <- PTRLENGTH(L)

Length. (Assumes elements of L are pointers)

Inputs
  L  : list (of pointers)

Outputs
  n  : the length of L, i.e. # of pointers represented in L.
======================================================================*/
#include "saclib.h"

Word PTRLENGTH(L)
       Word L;
{
#if __WORDSIZE == 64
  return LENGTH(L)/4;
#else /* Assumes 32-bit pointers. */
  return LENGTH(L)/2;
#endif

}
