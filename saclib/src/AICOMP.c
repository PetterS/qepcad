/*=======================================================================
                        s <- AICOMP(A,B)

Array integer comparison.

Inputs
   A, B : array integers.

Output
   s : 0, -1 or 1, the sign of A - B.
========================================================================*/
#include "saclib.h"

BDigit AICOMP(A,B)
	BDigit *A,*B;
{
	BDigit d,i,m,n,s,t,u;

Step1: /* Different signs or both zero. */
	t = A[0];
	u = B[0];
	if (t > u) {
	   s = 1;
	   goto Return; }
	if (t < u) {
	   s = -1;
	   goto Return; }
	if (t == 0) {
	   s = 0;
	   goto Return; }

Step2: /* Different lengths. */
	m = A[1];
	n = B[1];
	if (m > n) {
	   s = t;
	   goto Return; }
	if (m < n) {
	   s = -t;
	   goto Return; }

Step3: /* Compare magnitudes. */
	for (i = n + 1; i >= 2; i--) {
	   d = A[i] - B[i];
	   if (d > 0) {
	      s = t;
	      goto Return; }
	   if (d < 0) {
	      s = -t;
	      goto Return; } }
	s = 0;

Return: /* Return s. */
	return(s);
}
