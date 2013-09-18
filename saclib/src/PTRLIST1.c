/*======================================================================
                      L <- PTRLIST1(a)

List, 1 element.

Inputs
  a  : a pointer (i.e. Word*).

Outputs
  L  : the list (a).
======================================================================*/
#include "saclib.h"
Word PTRLIST1(a)
Word *a;
{
return PTRCOMP(a,NIL); 
}

