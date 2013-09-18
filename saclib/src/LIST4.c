/*======================================================================
                      L <- LIST4(a1,a2,a3,a4)

List, 4 elements.

Inputs
  a1, a2, a3, a4  : objects.

Outputs
  L  : the list (a1,a2,a3,a4).
======================================================================*/
#include "saclib.h"

Word LIST4(a1,a2,a3,a4)
       Word a1,a2,a3,a4;
{
       Word L;

Step1: /* Compute. */
       L = COMP(a1,COMP(a2,COMP(a3,COMP(a4,NIL))));

Return: /* Prepare for return. */
       return(L);
}
