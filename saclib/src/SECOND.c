/*======================================================================
<macro>               a <- SECOND(L)

Second.

Inputs
  L  : list of length 2 or more.

Outputs
  a  : the second element of L.
======================================================================*/
#ifndef NO_SACLIB_MACROS
#define NO_SACLIB_MACROS
#endif
#include "saclib.h"

Word SECOND(L)
       Word L;
{
       Word a;
       /* hide algorithm */

Step1: /* Get it. */
       a = FIRST(RED(L));

Return: /* Prepare for return. */
       return(a);
}
