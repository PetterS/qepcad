/*===========================================================================
			   s <- IACOMPA(A,m,B,n)

Integer absolute value comparison, array version.

Inputs
  A, B : in Z, in array representation.
  m, n : BETA-digits, m = length(A), n = length(B).

Outputs
  s = sign(|A|-|B|).
===========================================================================*/
#include "saclib.h"

Word IACOMPA(A,m,B,n)
       Word *A,m,*B,n;
{
       Word a,b,i,s;

Step1: /* Different lengths. */
       if (m > n) {
	  s = 1;
	  goto Return; }
       if (m < n) {
	  s = -1;
	  goto Return; }

Step2: /* Compare corresponding digits. */
       i = m;
       do {
	  i--;
	  a = A[i];
	  b = B[i];
	  a = absm(a);
	  b = absm(b);
	  s = a - b; }
       while (s == 0 && i > 0);

Return: /* Prepare for return. */
       return(s);
}
