/*======================================================================
			 b <- IUPLRB(A)

Integral univariate polynomial logarithmic root bound.

Inputs
  A : in Z[X], deg(A) > 0.

Outputs
  b : a logarithmic binary rational number which is a root 
      bound for A.  If A(x) = a_n x^n +...+ a_0, a_n /= 0, 
      then b is the smallest power of 2 such that
      2 |a_{n-k} / a_n|^{1/k} <= b for 1 <= k <= n.
      If a_{n-k} = 0 for 1 <= k <= n then b = 1.
======================================================================*/
#include "saclib.h"

Word IUPLRB(A)
       Word A;
{
       Word Ap,a,a1,ab,ab1,abp,b,d,h,h1,k,m,m1,n,n1,q,r,s,t;

Step1: /* Initialize. */
       ADV2(A,&n,&a,&Ap);
       if (Ap == NIL) {
	  h = -1;
	  goto Step3; }
       ab = IABSF(a);
       m = ILOG2(ab);
       t = 0;

Step2: /* Process terms. */
       do {
	  ADV2(Ap,&n1,&a1,&Ap);
	  k = n - n1;
	  m1 = ILOG2(a1);
	  d = m1 - m - 1;
	  QREM(d,k,&q,&r);
	  if (r < 0) {
	     r = r + k;
	     q = q - 1; }
	  h1 = q + 1;
	  if (r == k - 1) {
	     ab1 = IABSF(a1);
	     abp = ITRUNC(ab,-h1 * k);
	     s = ICOMP(ab1,abp);
	     if (s > 0)
		h1 = h1 + 1; }
	  if (t == 0 || h1 > h)
	     h = h1;
	  t = 1; }
       while (Ap != NIL);

Step3: /* Compute b. */
       h = h+ 1;
       b = LIST2(1,-h);

Return: /* Return b. */
       return(b);
}
