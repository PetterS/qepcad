/*=======================================================================
                             t <- AGINC(A,B)

Array Gaussian integer norm comparison.

Inputs
   A, B :  nonzero array Gaussian integers.

Output
   t : a BETA integer.  t = 1 or 2.  If t = 1, norm(A) <=
       (1 + e) * norm(B).  If t = 2, norm (B) <= (1 + e) * norm(A).
========================================================================*/
#include "saclib.h"

BDigit AGINC(A,B)
	BDigit **A,**B;
{
	BDigit a,a1,a2,b,b1,b2,k,k1,k2,n,n1,n2,t;

Step1: /* */
	AGIBL(A, &n1,&k1);
        AGIBL(B, &n2,&k2);
	n = n2 - n1;
	if (n > 1) {
	   t = 1;
	   goto Return; }
	if (n < -1) {
	   t = 2;
	   goto Return; }
	if (n == 1) {
	   n = n1;
	   k2 = k2 + ZETA; }
	else if (n == -1) {
	   n = n2;
	   k1 = k1 + ZETA; }
	n = n1;
	k = k2 - k1;
	if (k > 1) {
	   t = 1;
	   goto Return; }
	if (k < -1) {
	   t = 2;
	   goto Return; }
	k = MIN(k1,k2);
	if (k >= 10)
           k = k - 10;
        else {
           if (n > 0) {
              n = n - 1;
              k = ZETA + k - 10; }
	   else
	      k = 0; }
	a1 = AITRS(A[0],n,k);
        a2 = AITRS(A[1],n,k);
        b1 = AITRS(B[0],n,k);
        b2 = AITRS(B[1],n,k);
	a = a1 * a1 + a2 * a2;
	b = b1 * b1 + b2 * b2;
	if (a <= b)
	   t = 1;
	else
	   t = 2;

Return: /* Return t. */
	return(t);
}
