/*======================================================================
                      c <- EXPF(a,b)

Exponential function.  

Inputs
  a, b : C integers, b non-negative.

Outputs
  c : a^b, with 0^0=1.
======================================================================*/
#include "saclib.h"

Word EXPF(a,b)
       Word a,b;
{
       Word c,i;

Step1: /* Compute. */
       c = 1;
       for (i = 1; i <= b;  i++)
	  c = a * c;

Return: /* Prepare for return. */
       return(c);
}
