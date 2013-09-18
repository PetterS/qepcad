/*======================================================================
<macro>               c <- MDDIF(m,a,b)

Modular digit difference.  

Inputs
  m    : a positive BETA-integer.  
  a, b : elements of z/(m). 

Outpus
  c    : a - b.
======================================================================*/
#ifndef NO_SACLIB_MACROS
#define NO_SACLIB_MACROS
#endif
#include "saclib.h"

Word MDDIF(m,a,b)
       Word m,a,b;
{
       Word c;
       /* hide algorithm */

Step1: /* Compute. */
       c = a - b;
       if (c < 0)
         c = c + m;

Return: /* Prepare for return. */
       return(c);
}
