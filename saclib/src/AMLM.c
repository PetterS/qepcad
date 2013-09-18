/*======================================================================
                      L <- AMLM(M,m,n)

Array matrix to list matrix.

Inputs
   M : a matrix of beta digits in array representation.
   m, n : positive beta digits, the numbers of rows and
          columns respectively in M.

Output
  L  : the matrix M in list representation.
======================================================================*/
#include "saclib.h"

Word AMLM(M,m,n)
	BDigit **M,m,n;
{
	BDigit i,j;
        Word L,L1;

Step1: /* Construct L. */
	L = NIL;
	for (i = m-1; i >= 0; i--) {
	   L1 = NIL;
	   for (j = n-1; j >= 0; j--)
	      L1 = COMP(M[i][j],L1);
	   L = COMP(L1,L); }

Return: /* Return L. */
	return(L);
}
