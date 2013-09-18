/*======================================================================
                      s <- SIGN(a)

Sign.  

Inputs
  a : a C integer.  

Outputs
  s : the sign of a.
======================================================================*/
#include "saclib.h"

Word SIGN(a)
       Word a;
{
       Word s;

Step1: /* Compute. */
       if (a > 0)
	  s = 1;
       else
	  if (a < 0)
	     s = -1;
	  else
	     s = 0;

Return: /* Prepare for return. */
       return(s);
}
