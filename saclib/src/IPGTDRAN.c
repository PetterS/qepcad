/*====================================================================
                        A <- IPGTDRAN(r,k,q,n)

Integral polynomial, guaranteed total degree, random.

Inputs
   r : BETA-digit r >= 1.
   k : a positive BETA-digit.
   q : in Q, q = q1 / q2 with 0 < q1 <= q2 < BETA.  
   n : a non-negative BETA-digit.

Output
   A : an integral polynomial in r variables of total degree n.
       For 1 <= i <= r, the coefficient of x_i^n in A is nonzero. 
       For all other terms of A, the coefficient is nonzero with
       probability q.  Nonzero coefficients are random k-bit integers.
=====================================================================*/
#include "saclib.h"

Word IPGTDRAN(r,k,q,n)
	BDigit r,k,n;
        Word q;
{
	BDigit i,j,m,q1,q2,qs,t;
        Word a,A,A1,E;

Step1: /* Apply IPSTDRAN. */
	A = IPSTDRAN(r,k,q,n);

Step2: /* Include terms x_i^{n}. */
	FIRST2(q,&q1,&q2);
        DQR(q1,0,q2,&qs,&t);
	for (i = 1; i <= r; i++) {
	   m = PDEGSV(r,A,i);
	   if (m < n) {
	      do
	         a = IRAND(k);
	      while (a == 0);
	      E = NIL;
	      for (j = 1; j <= i - 1; j++)
	         E = COMP(0,E);
	      E = COMP(n,E);
	      for (j = 1; j <= r - i; j++)
	         E = COMP(0,E);
	      A1 = LIST2(a,E);
	      A1 = PFDIP(r,A1);
	      A = IPSUM(r,A,A1); } }

Return: /* Return A. */
	return(A);
}
