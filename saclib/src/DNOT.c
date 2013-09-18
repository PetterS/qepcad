/*======================================================================
<macro>               b <- DNOT(a)

Digit not.

Inputs
  a : a non-negative BETA-digit.

Outputs
  b : the bit-wise not of a.
======================================================================*/
#ifndef NO_SACLIB_MACROS
#define NO_SACLIB_MACROS
#endif
#include "saclib.h"

Word DNOT(a)
       Word a;
{
       Word b;
       /* hide b; */

Step1: /* Compute. */
       b = BETA1 - a;

Return: /* Prepare for return. */
       return(b);
}
