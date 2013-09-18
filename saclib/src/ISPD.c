/*===========================================================================
			  ISPD(n; F,m)

Integer small prime divisors.

Inputs
  n   : in Z. n > 0.

Outputs
  F,m : F is a list of primes (q_1,q_2,...,q_h), h non-negative,
        q_1 <= q_2 <= ... <= q_h, such that n is equal to m
	times the product of the q_i  and m is not divisible by
	any prime in SPRIME.  Either m=1 or m > p^2 + 1, where p
	is the largest element in SPRIME.
===========================================================================*/
#include "saclib.h"

void ISPD(n, F_,m_)
       Word n, *F_,*m_;
{
       Word F,Lp,m,p,q,r;

Step1: /* Compute. */
       F = NIL;
       m = n;
       Lp = SPRIME;
       do {
	  p = FIRST(Lp);
	  if (m < BETA)
	     QREM(m,p,&q,&r);
	  else
	     IDQR(m,p,&q,&r);
	  if (r == 0) {
	     F = COMP(p,F);
	     m = q; }
	  else
	     Lp = RED(Lp); }
       while (q > p && Lp != NIL);
       if (q <= p && m != 1) {
	  F = COMP(m,F);
	  m = 1; }
       F = INV(F);

Return: /* Prepare for return. */
       *F_ = F;
       *m_ = m;
       return;
}
