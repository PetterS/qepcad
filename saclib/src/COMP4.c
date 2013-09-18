/*======================================================================
                      M <- COMP4(a1,a2,a3,a4,L)

Composition 4.

Inputs
  a1, a2, a3, a4  : objects.
  L               : list.

Outputs
  M               : COMP(a1,COMP(a2,COMP(a3,COMP(a4,L)))).
======================================================================*/
#include "saclib.h"

Word COMP4(a1,a2,a3,a4,L)
       Word a1,a2,a3,a4,L;
{
       Word M;

Step1: /* Compose. */
       M = COMP(a1,COMP(a2,COMP(a3,COMP(a4,L))));

Return: /* Prepare for return. */
       return(M);
}
