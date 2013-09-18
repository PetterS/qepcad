/*=====================================================================
                       A <- LBRN(a,k)

Logarithmic binary rational number.

Input
   a : an odd integer.
   k : a BETA-digit.

Output
   A : the binary rational number a/2^k in logarithmic representation.
=====================================================================*/
#include "saclib.h"

Word LBRN(a,k)
       BDigit k;
       Word a;
{
       Word A;

Step1: /* Make a list. */
       A = LIST2(a,k);

Return: /* Return A. */
	return(A);
}
