/*======================================================================
                           B <- HIPTR1(n,A)

Hardware interval polynomial translation by 1.

Inputs
    n : a BETA-digit, n >= 1.
    A : in HI[X], deg(A) = n.

Output
    B : in HI[X], B(x) = A(x + 1).

Remark
   HIPTR1 is not floating-point overflow-underflow protected.
======================================================================*/
#include "saclib.h"

interval *HIPTR1(n,A)
	BDigit n;
	interval A[];
{
	interval a,*B;
	BDigit i,j;

Step1: /* Copy A into B. */
	B = HIPCOPY(n,A);

Step2: /* Apply synthetic division. */
	for (i = 0; i < n; i++) {
	   a = A[n];
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
