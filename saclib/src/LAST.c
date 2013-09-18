/*======================================================================
                      l <- LAST(L)

Last element of list.

Inputs
  L  : a non-empty list.
  
Outputs
  l  : the last element of L.
======================================================================*/
#include "saclib.h"

Word LAST(L)
      Word L;
{
      Word a;
Step1: /* Extract the element in the last cell of L. */
      a = FIRST(LASTCELL(L));

Return: /* Return a. */
      return(a);
}
