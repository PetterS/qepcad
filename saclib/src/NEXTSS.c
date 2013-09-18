/*=======================================================================
                          t <- NEXTSS(n,m,A)

Next subset.

Inputs
   n, m : positive beta digits, m <= n.
   A : An array of m integers representing an ascending m-tuple of
       integers from {1,2,...,n}.  Ascending means that A[i] < A[i+1]
       for 1 <= i < m.
      

Output
   t : 0 or 1.

Effect
   If the content of A is lexicographically last among all ascending
   m-tuples from {1,2,...,n}, then t = 0.  Otherwise t = 1 and the
   content of A is changed to represent the lexicographically next
   ascending m-tuple from {1,2,...,n}.
========================================================================*/
#include "saclib.h"

BDigit NEXTSS(n,m,A)
	BDigit n,m,*A;
{
	BDigit i,j,t;

Step1: /* Find rightmost increasable element, if any. */
	for (i = 1; i <= m; i++) {
	   if (A[m-i] < n - i + 1)
	      goto Step3; }
	   
Step2: /* Lexicographically last. */
	t = 0;
	goto Return;

Step3: /* Produce next m-tuple. */
	A[m-i] = A[m-i] + 1;
	for (j = m-i+1; j < m; j++)
	   A[j] = A[j-1] + 1;
	t = 1;

Return: /* Return t. */
	return(t);
}
