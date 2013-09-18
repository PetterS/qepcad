/*===========================================================================
			     M <- IDENTMAT(n)

Identity matrix.

Input:
 n : a non-negative BETA-digit.
  
Ouput
 M : the n by n integer identity matrix.
===========================================================================*/
#include "saclib.h"

Word IDENTMAT(n)
       Word n;
{
       Word M,M1,i,j;

Step1: /* Construct. */
       M = NIL;
       for (i = 1; i <= n; i++) {
	  M1 = NIL;
	  for (j = 1; j <= n; j++)
	     if (i == j)
		M1 = COMP(1,M1);
	     else M1 = COMP(0,M1);
	  M = COMP(M1,M); }

Return: /* Prepare for return. */
       return(M);
}
