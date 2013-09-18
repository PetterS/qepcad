/*========================================================================
                           B <- AII(A)

Array integer to integer.

Input
   A : an integer in array representation.

Output
   B : the integer in list representation.

========================================================================*/
#include "saclib.h"

Word AII(A)
	BDigit *A;
{
	Word *Ap,B;
	BDigit b,i,n,s;

Step1: /* Single precision. */
	s = A[0];
        n = A[1];
	if (s == 0) {
	   B = 0;
	   goto Return; }
	if (n == 1) {
	   B = A[2];
	   if (s < 0)
	      B = - B;
	   goto Return; }

Step2: /* Multiple precision. */
	Ap = A + 2;
	B = NIL;
	for (i = n - 1; i >= 0; i--) {
	   b = Ap[i];
	   if (s < 0)
	      b = - b;
	   B = COMP(b,B); }
	
Return: /* Return B. */
	return(B);
}
