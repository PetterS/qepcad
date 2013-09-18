/*======================================================================
                           B <- HIPCHT(n,A)

Hardware interval polynomial circle to half-plane transformation.

Inputs
    n : a BETA-digit, n >= 1.
    A : in HI[X], deg(A) = n.

Output
    B : in HI[X].  Let A'(x) = x^n A(1/x).  Then B(x) = A'(x + 1).
======================================================================*/
#include "saclib.h"

interval *HIPCHT(n,A)
	BDigit n;
	interval A[];
{
	interval a,*B;
	BDigit i,j;

Step1: /* Put reciprocal transform of A into B. */
	B = HIPRT(n,A);

Step2: /* Translate by 1. */
	for (i = 0; i < n; i++) {
	   a = A[0];
	   rounddown();
	   for (j = n-1; j >= i; j--) {
	      a.left = a.left + B[j].left;
	      B[j].left = a.left; }
	   roundup(); 
	   for (j = n-1; j >= i; j--) {
	      a.right= a.right + B[j].right;
	      B[j].right = a.right; } }

Return: /* Return B. */
	return(B);
}
