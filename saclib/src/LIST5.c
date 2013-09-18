/*======================================================================
                      L <- LIST5(a1,a2,a3,a4,a5)

List, 5 elements.

Inputs
  a1,a2,a3,a4, a5  : objects.

Outputs
  L  : the list (a1,a2,a3,a4,a5).
======================================================================*/
#include "saclib.h"

Word LIST5(a1,a2,a3,a4,a5)
       Word a1,a2,a3,a4,a5;
{
       Word L;

Step1: /* Compute. */
       L = COMP(a1,COMP(a2,COMP(a3,COMP(a4,COMP(a5,NIL)))));

Return: /* Prepare for return. */
       return(L);
}
