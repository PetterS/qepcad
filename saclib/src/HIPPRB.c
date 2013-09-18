/*======================================================================
                      k <- HIPPRB(n,A)

Hardware interval polynomial positive root bound.

Inputs
   n : a positive beta-digit.
   A : a hardware integral polynomial of degree n such that A[n]
       does not contain zero.

Output
   k : If all nonzero coefficients of A have the same sign,
       then A has no positive roots and k = NIL.  Otherwise
       k is the least positive integer such that for all i,
       1 <= i < n, 2 (-a_{n-1} / a_n)^{1/i} <=  k, a beta-digit
       such that all positive roots are less than 2^k.
======================================================================*/
#include "saclib.h"

BDigit HIPPRB(n,A)
	BDigit n;
	interval *A;

{
	BDigit d,e,f,i,j,q,r,s,t;
	Word k;

Step1: /* Branch on sign of leading coefficient. */
	k = NIL;
	s = HSIGN(A[n].right);
	if (s < 0)
	   goto Step3;

Step2: /* A[n] > 0, process terms. */
	e = HEXP(A[n].left);
	for (i = n - 1; i >= 0; i--) {
	   t = HSIGN(A[i].left);
	   if (t < 0) {
	      f = HEXP(A[i].left);
	      j = n - i;
	      d = f - e + 1;
	      QREM(d,j,&q,&r);
	      if (r > 0) {
	         r = r - j;
	         q = q + 1; }
	      if (k == NIL || q > k)
	         k = q; } }
	if (k != NIL)
	   k = k + 1;
	goto Return;

Step3: /* A[n] < 0, process terms. */
        e = HEXP(A[n].right);
        for (i = n - 1; i >= 0; i--) {
           t = HSIGN(A[i].right);
           if (t > 0) {
              f = HEXP(A[i].right);
              j = n - i;
              d = f - e + 1;
              QREM(d,j,&q,&r);
              if (r > 0) {
                 r = r - j;
                 q = q + 1; }
              if (k == NIL || q > k)
                 k = q; } }
	if (k != NIL)
           k = k + 1;

Return: /* Return k. */
	return(k);
}
