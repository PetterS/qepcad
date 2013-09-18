/*=====================================================================
                       s <- LBRNSIGN(A)

Logarithmic binary rational number sign.

Input
   A : a logarithmic binary rational number.

Output
   s : sign(A), an integer.
=====================================================================*/
#include "saclib.h"

Word LBRNSIGN(A)
       Word A;
{
       Word s;

Step1: /* Use sign of numerator. */
       if (A == 0)
	  s = 0;
       else 
	  s = ISIGNF(FIRST(A));

Return: /* Return s. */
	return(s);
}
