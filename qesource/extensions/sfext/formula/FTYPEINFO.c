/*======================================================================
                 FTYPEINFO(F)

Formula type information.

Inputs
 F : A formula.
Output
 T : The type of the formula:  NIL if F is an atom, ANDOP if it's a
     conjunction, and OROP if it's a disjunction.
======================================================================*/
#include "qepcad.h"

Word FTYPEINFO(Word A)
{
  if (ISLIST(FIRST(A)))
    return NIL;
  if (FIRST(A) == ANDOP)
    return ANDOP;
  if (FIRST(A) == OROP)
    return OROP;
  if (FIRST(A) == TRUE)
    return TRUE;
  if (FIRST(A) == FALSE)
    return FALSE;
  
}
      
