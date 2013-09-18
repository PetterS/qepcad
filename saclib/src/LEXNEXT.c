/*=======================================================================
                          t <- LEXNEXT(n,m,A)

Lexicographically next.

Inputs
   n, m : positive beta digits.
   A : an array of n integers from the interval [0,m].

Output
   t :  0 or 1.

Effect
   The content of A represents an element (A[n-1],...,A[1],A[0]) 
   from the set [0,m]^n.  If this element is lexicographically
   last, then t = 0 and A is changed to represent the element
   that is lexicographically first.  Otherwise t = 1 and A is
   element that is lexicographically next.
========================================================================*/
#include "saclib.h"

BDigit LEXNEXT(n,m,A)
	BDigit n,m,*A;
{
	BDigit i,t;

Step1: /* Search. */
	t = 0;
	for (i = 0; i < n; i++) {
	   if (A[i] < m) {
	      A[i] = A[i] + 1;
	      t = 1;
	      goto Return; }
	   A[i] = 0; }
	   
Return: /* Return t. */
	return(t);
}
