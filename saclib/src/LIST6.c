/*===========================================================================
		       L <- LIST6(a1,a2,a3,a4,a5,a6)

List, 6 elements.

Inputs
  a1, a2, a3, a4, a5, a6 : objects.

Output
  L : the list (a1,a2,a3,a4,a5,a6).
===========================================================================*/
#include "saclib.h"

Word LIST6(a1,a2,a3,a4,a5,a6)
       Word a1,a2,a3,a4,a5,a6;
{
       Word L;

Step1: /* Construct. */
       L = COMP(a1,COMP(a2,COMP(a3,COMP(a4,COMP(a5,COMP(a6,NIL))))));

Return: /* Prepare for return. */
       return(L);
}
