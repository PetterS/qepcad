/*========================================================================
                           B = IAI(A)

Integer to array integer.

Input
   A : an integer.

Output
   B : The array representation of A.
========================================================================*/
#include "saclib.h"

BDigit *IAI(A)
	Word A;
{
	BDigit *B,i,n;
	Word Ap;

Step1: /* A a beta-digit. */
	if (A < BETA) {
	   B = GETARRAY(3);
	   B[2] = ABS(A);
	   if (A == 0) {
	      B[0] = 0;
	      B[1] = 0; }
	   else {
	      B[1] = 1;
	      if (A > 0)
	         B[0] = 1;
	      else
	         B[0] = -1; }
	   goto Return; }

Step2: /* Compute the length of A and get an array. */
	n = LENGTH(A);
	B = GETARRAY(n + 2);
	B[1] = n;

Step3: /* Copy the beta-digits. */
	Ap = A;
	for (i = 1; i < n; i++) {
	   B[i + 1] = ABS(FIRST(Ap));
	   Ap = RED(Ap); }
	B[n + 1] = ABS(FIRST(Ap));
	
Step4: /* Store the sign of A. */
	if (FIRST(Ap) > 0)
	   B[0] = 1;
	else
	   B[0] = -1;
	
Return: /* Return B. */
	return(B);
}
