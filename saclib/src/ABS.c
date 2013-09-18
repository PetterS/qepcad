/*===========================================================================
				b <- ABS(a)

Absolute value.  

Inputs
  a : a C integer.

Outputs
  b : the absolute value of a.
===========================================================================*/
#include "saclib.h"

Word ABS(a)
       Word a;
{
       Word b;

Step1: /* Get the absolute value. */
       if (a >= 0)
	  b = a;
       else
	  b = -a;

Return: /* Prepare for return. */
       return(b);
}
