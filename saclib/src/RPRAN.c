/*===========================================================================
			    A <- RPRAN(r,k,q,N)

Rational polynomial, random.

Inputs
  r : BETA-digit r >= 0.
  k : a positive BETA-digit.
  q : in Q, q = q1/q2 with 0 < q1 <= q2 < BETA.  
  N : a list (n_r,...,n_1) of non-negative BETA-digits.

Outputs
  A : in Q[x_1,...,x_r], a random rational polynomial with deg_i(A) <= n_i
      for 1 <= i <= r.  Each rational number coefficient of A is
      a / (|b| + 1) where a and b are random k-bit integers.  q is
      the expected density of A, that is, the probability that any 
      particular rational number coefficient of A is non-zero.
===========================================================================*/
#include "saclib.h"

Word RPRAN(r,k,q,N)
       Word r,k,q,N;
{
       Word A,Np,a,d,e,n,q1,q2,qs,rp,t;

Step1: /* Compute qls=int(q*BETA). */
       FIRST2(q,&q1,&q2);
       DQR(q1,0,q2,&qs,&t);

Step2: /* r=0. */
       if (r == 0) {
	  d = DRANN();
	  if (d < qs)
	     A = RNRAND(k);
	  else
	     A = 0;
	  goto Return; }

Step3: /* r > 0. */
       rp = r - 1;
       ADV(N,&n,&Np);
       A = NIL;
       for (e = 0; e <= n; e++) {
	  if (rp == 0) {
	     d = DRANN();
	     if (d < qs)
		a = RNRAND(k);
	     else
		a = 0; }
	  else
	     a = RPRAN(rp,k,q,Np);
	  if (a != 0)
	     A = COMP2(e,a,A); }
       if (A == NIL)
	  A = 0;

Return: /* Prepare for return. */
       return(A);
}
