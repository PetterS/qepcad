/*======================================================================
			 b <- IUPPRB(A)

Integral univariate polynomial positive root bound.

Inputs
  A : in Z[x], deg(A) > 0, A(0) /= 0.

Outputs
  b : a logarithmic binary rational number that is an upper
      bound for the positive roots of A.  Let A(x) = a_n x^n
      +...+ a_0 with n = deg(A).  If a_{n-k} / a_n >= 0
      for all k, then b = 0.  Otherwise, b is the least
      power of 2 such that, for every k with 1 <= k <= n,
      2 (-a_{n-k} / a_n )^{1/k} <= b.
======================================================================*/
#include "saclib.h"

Word IUPPRB(A)
       Word A;
{
       Word d,h,h1,k,m,m1,n,n1,q,r,s,s1,t;
       Word Ap,a,a1,ap,b;

Step1: /* Initialize. */
       t = 0;
       h = 0;
       ADV2(A,&n,&a,&Ap);
       if (Ap == NIL) {
	  h = -1;
	  goto Step3; }
       s = ISIGNF(a);
       if (s < 0)
	  a = INEG(a);
       m = ILOG2(a);

Step2: /* Process terms. */
       do {
	  ADV2(Ap,&n1,&a1,&Ap);
	  s1 = ISIGNF(a1);
	  if (s != s1) {
	     k = n - n1;
	     m1 = ILOG2(a1);
	     d = m1 - m - 1;
	     QREM(d,k,&q,&r);
	     if (r < 0) {
		r = r + k;
		q = q - 1; }
	     h1 = q + 1;
	     if (r == k - 1) {
		if (s1 < 0)
		   a1 = INEG(a1);
		ap = ITRUNC(a,-h1 * k);
		if (ICOMP(a1,ap) > 0)
		   h1 = h1 + 1; }
	     if (t == 0 || h1 > h)
		h = h1;
	     t = 1; } }
       while (Ap != NIL);

Step3: /* Compute b. */
       if (t == 0)
	  b = 0;
       else 
	  b = LIST2(1,-h -1);

Return: /* Prepare for return. */
       return(b);
}
