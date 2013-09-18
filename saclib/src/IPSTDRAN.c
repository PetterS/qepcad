/*====================================================================
                        A <- IPSTDRAN(r,k,q,n)

Integral polynomial, specified total degree, random.

Inputs
   r : BETA-digit r >= 0.
   k : a positive BETA-digit.
   q : in Q, q = q1 / q2 with 0 < q1 <= q2 < BETA.  
   n : a non-negative BETA-digit.

Output
   A : in Z[x_1,...,x_r], a random integral polynomial in r
       variables of total degree <= n and target density of
       q, with random k-bit coefficients.
=====================================================================*/
#include "saclib.h"

Word IPSTDRAN(r,k,q,n)
	Word r,k,q,n;
{
	Word A,A1,d,i,q1,q2,qs,t;

Step1: /* Approximate q * BETA. */
	FIRST2(q,&q1,&q2);
	DQR(q1,0,q2,&qs,&t);

Step2: /* r = 0. */
	if (r > 0)
	   goto Step3;
        d = DRANN();
	if (d < qs)
	   A = IRAND(k);
	else
	   A = 0;
	goto Return;

Step3: /* r >= 1. */
	A = NIL;
	for (i = 0; i <= n; i++) {
	   A1 = IPSTDRAN(r - 1,k,q,n - i);
	   if (A1 != 0)
	      A = COMP2(i,A1,A); }
	if (A == NIL)
	   A = 0;

Return: /* Return A. */
	return(A);
}
