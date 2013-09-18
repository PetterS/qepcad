/*======================================================================
<macro>               c <- MDSUM(m,a,b)

Modular digit sum.  

Inputs
  m   : a positive BETA-integer.  
  a,b : elements of Z_m.

Outputs
  c   : a + b.
======================================================================*/
#ifndef NO_SACLIB_MACROS
#define NO_SACLIB_MACROS
#endif
#include "saclib.h"

Word MDSUM(m,a,b)
       Word m,a,b;
{
       Word c,cp;
       /* hide algorithm */

Step1: /* Compute. */
       c = a + b;
       cp = c - m;
       if (cp >= 0)
         c = cp;

Return: /* Prepare for return. */
       return(c);
}
