/*======================================================================
                      L <- LIST10(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10)

List, 10 elements.

Iputs
  a1, a2, a3, a4, a5, a6, a7, a8, a9, a10  : objects.

Outputs
  L  : the list (a1,a2,a3,a4,a5,a6,a7,a8,a9,a10).
======================================================================*/
#include "saclib.h"

Word LIST10(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10)
       Word a1,a2,a3,a4,a5,a6,a7,a8,a9,a10;
{
       Word L;

Step1: /* Compute. */
       L = COMP(a1,COMP(a2,COMP(a3,COMP(a4,COMP(a5,COMP(a6,COMP(a7,COMP(a8,COMP(a9,COMP(a10,NIL))))))))));

Return: /* Prepare for return. */
       return(L);
}
