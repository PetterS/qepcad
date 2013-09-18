/*=======================================================================
                         IPCA(r,A; n,h,k,t)

Integral polynomial coefficient analysis.

Inputs
   r : a positive beta digit.
   A : an integral  polynomial in r variables.

Outputs
   n : the number of monomials in A.
   h : the minimum number of bits in any nonzero integer coefficient of A.
   k : the maximum number of bits in any nonzero integer coefficient of A.
   t : the total number of bits in all of the integer coefficients of A.
===========================================================================*/
#include "saclib.h"

void IPCA(r,A, n_,h_,k_,t_)
	BDigit r;
	Word A;
	BDigit *n_,*h_,*k_,*t_;
{
	BDigit h,h1,j,k,k1,n,n1,rp,t,t1;
	Word a,Ap;

Step1: /* A = 0. */
	n = 0;
	h = 0;
	k = 0;
	t = 0;
	if (A == 0)
	   goto Return;

Step2: /* r = 1. */
	if (r == 1) {
	   Ap = A;
	   h = BETA1;
	   while (Ap != NIL) {
	      a = SECOND(Ap);
	      n = n + 1;
	      j = ILOG2(a);
	      if (j < h)
	         h = j;
	      if (j > k)
	         k = j;
	      t = t + j;
	      Ap = RED2(Ap); }
	   goto Return; }

Step3: /* r > 1. */
	Ap = A;
	rp = r - 1;
	h = BETA1;
	while (Ap != NIL) {
	   a = SECOND(Ap);
	   IPCA(rp,a,&n1,&h1,&k1,&t1);
	   n = n + n1;
	   if (h1 < h)
	      h = h1;
	   if (k1 > k)
	      k = k1;
	   t = t + t1;
	   Ap = RED2(Ap); }

Return: /* Return n, h, k and t. */
	*n_ = n;
	*h_ = h;
	*k_ = k;
	*t_ = t;
}
