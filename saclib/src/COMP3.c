/*======================================================================
                      M <- COMP3(a1,a2,a3,L)

Composition 3.

Inputs
  a1, a2, a3  : objects
  L           : list
Outputs
  M           : COMP(a1,COMP(a2,COMP(a3,L))).
======================================================================*/
#include "saclib.h"

Word COMP3(a1,a2,a3,L)
       Word a1,a2,a3,L;
{
       Word M;

Step1: /* Compose. */
       M = COMP(a1,COMP(a2,COMP(a3,L)));

Return: /* Prepare for return. */
       return(M);
}
