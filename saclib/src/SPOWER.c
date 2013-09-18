/*===========================================================================
			     t <- SPOWER(s,a)

Sign power.

Input
  s : a sign.
  a : a non-negative BETA-digit.

Ouput
  t : t = s^a.
===========================================================================*/
#include "saclib.h"

Word SPOWER(s,a)
       Word s,a;
{
       Word c;

Step1: /* Compute. */
       if (a == 0)
	  c = 1;
       else
	  if (s == 0)
	     c = 0;
	  else
	     if (ODD(a) && s == -1)
		c = -1;
	     else
		c = 1;

Return: /* Prepare for return. */
       return(c);
}
