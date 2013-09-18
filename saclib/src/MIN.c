/*======================================================================
                      c <- MIN(a,b)

Minimum.  

Inputs
  a, b : C integers.  

Outputs
  c    : the minimum of a and b.
======================================================================*/
#include "saclib.h"

Word MIN(a,b)
       Word a,b;
{
       Word c;

Step1: /* Compute. */
       if (a <= b)
	  c = a;
       else
	  c = b;

Return: /* Prepare for return. */
       return(c);
}
