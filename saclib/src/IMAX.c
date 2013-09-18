/*======================================================================
                      c <- IMAX(a,b)

Integer maximum.  

Inputs
  a,b : in Z.

Outputs
  c   : the maximum of a and b.
======================================================================*/
#include "saclib.h"

Word IMAX(a,b)
       Word a,b;
{
       Word c,s;
       /* hide algorithm */

Step1: /* Compute. */
       s = ICOMP(a,b);
       if (s >= 0)
         c = a;
       else
         c = b;

Return: /* Prepare for return. */
       return(c);
}
