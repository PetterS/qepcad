/*======================================================================
                      s <- HSIGN(a)

Hardware sign.

Input
   a : a hardware double precision number.

Output
   s : The sign of a.
======================================================================*/
#include "saclib.h"

BDigit HSIGN(a)
	double a;
{
	BDigit s;

Step1: /* Obtain sign. */
	if (a > 0)
	   s = 1;
	else if (a < 0)
	   s = -1;
	else
	   s = 0;

Return: /* Return s. */
	return(s);
}
