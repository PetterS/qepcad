/*===========================================================================
			       c <- MAX(a,b)

Maximum.  

Inputs
  a, b : C integers.  

Output
  c    : the maximum of a and b.
===========================================================================*/
#include "saclib.h"

Word MAX(a,b)
       Word a,b;
{
       Word c;

Step1: /* Compute. */
       if (a >= b)
	  c = a;
       else
	  c = b;

Return: /* Prepare for return. */
       return(c);
}
