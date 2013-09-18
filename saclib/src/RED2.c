/*======================================================================
<macro>               Lp <- RED2(L)

Reductum 2.

Inputs
  L  : list of length 2 or more.

Outputs
  Lp  : the second reductum of L.
======================================================================*/
#ifndef NO_SACLIB_MACROS
#define NO_SACLIB_MACROS
#endif
#include "saclib.h"

Word RED2(L)
       Word L;
{
       Word Lp;
       /* hide algorithm */

Step1: /* Compute. */
       Lp = RED(RED(L));

Return: /* Prepare for return. */
       return(Lp);
}
