/*======================================================================
                      M <- RED4(L)

Reductum 4.

Inputs
  L  : list of length 4 or more.

Outputs
  M  : the fourth reductum of L.
======================================================================*/
#include "saclib.h"

Word RED4(L)
       Word L;
{
       Word M;
       /* hide algorithm */

Step1: /* Compute. */
       M = RED(RED(RED(RED(L))));

Return: /* Prepare for return. */
       return(M);
}
