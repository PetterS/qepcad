/*======================================================================
                      L <- LIST3(a1,a2,a3)

List, 3 elements.

Inputs
  a1, a2, a3  : objects.

Outputs
  L  : the list (a1,a2,a3).
======================================================================*/
#include "saclib.h"

Word LIST3(a1,a2,a3)
       Word a1,a2,a3;
{
       Word L;

Step1: /* Compute. */
       L = COMP(a1,COMP(a2,COMP(a3,NIL)));

Return: /* Prepare for return. */
       return(L);
}
