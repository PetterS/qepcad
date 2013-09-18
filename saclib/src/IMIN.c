/*======================================================================
                      c <- IMIN(a,b)

Integer minimum.  

Inputs
  a, b  : in Z.  

Outputs
  c     : the minimum of a and b.
======================================================================*/
#include "saclib.h"

Word IMIN(a,b)
       Word a,b;
{
       Word c,s;
       /* hide algorithm */

Step1: /* Compute. */
       s = ICOMP(a,b);
       if (s <= 0)
         c = a;
       else
         c = b;

Return: /* Prepare for return. */
       return(c);
}
