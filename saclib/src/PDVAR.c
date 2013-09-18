/*=======================================================================
                         t <- PDVAR(r,A,i)

Polynomial divisibility by a variable.

Inputs
   r : a positive beta digit.
   A : a nonzero polynomial in r variables.
   i : 1 <= i <= r.

Output
   t : 1 if A is divisible by x_i, 0 otherwise.
=======================================================================*/
#include "saclib.h"

BDigit PDVAR(r,A,i)
	BDigit r,i;
	Word A;
{
	BDigit n,t;
	Word B,B1,C;

Step1: /* Case i = r. */
	if (i == r) {
	   B = A;
	   C = RED2(B);
	   while (C != NIL) {
	      B = C;
	      C = RED2(B); }
	   n = PDEG(B);
	   if (n == 0)
	      t = 0;
	   else
	      t = 1;
	   goto Return; }

Step2: /* Case i < r. */
	B = A;
	while (B != NIL) {
	   B1 = PLDCF(B);
	   t = PDVAR(r - 1,B1,i);
	   if (t == 0)
	      goto Return;
	   B = RED2(B); }
	goto Return;

Return: /* Return t. */
	return(t);
}
