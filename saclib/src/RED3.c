/*======================================================================
                      M <- RED3(L)

Reductum 3.

Inputs
  L  : list of length 3 or more.

Outputs
  M  : the third reductum of L.
======================================================================*/
#include "saclib.h"

Word RED3(L)
       Word L;
{
       Word M;
       /* hide algorithm */

Step1: /* Compute. */
       M = RED(RED2(L));

Return: /* Prepare for return. */
       return(M);
}
