/*======================================================================
<macro>                b <- MDNEG(m,a)

Modular digit negative.  

Inputs
  m : a positive BETA-integer.  
  a : an element of Z_m.

Outputs
  b : -a.
======================================================================*/
#ifndef NO_SACLIB_MACROS
#define NO_SACLIB_MACROS
#endif
#include "saclib.h"

Word MDNEG(m,a)
       Word m,a;
{
       Word b;
       /* hide algorithm */

Step1: /* Compute. */
       if (a == 0)
         b = 0;
       else
         b = m - a;

Return: /* Prepare for return. */
       return(b);
}
