/*===========================================================================
			       QREM(a,b; q,r)

Quotient and remainder.

Inputs
  a, b : C integers, b non-zero.

Outputs
  q    : integral part of a / b.
  r    : a - b * q.
===========================================================================*/
#include "saclib.h"

void QREM(a,b, q_,r_)
       Word a,b, *q_,*r_;
{
       Word q,r;

Step1: /* Compute q. */
       if (a == 0)
	  q = 0;
       else if (a > 0) {
	  if (b > 0)
	     q = a / b;
	  else
	     q = -(a / -b); }
       else {
	  if (b > 0)
	     q = -(-a / b);
	  else 
	     q = -a / -b; }

Step2: /* Compute r. */
       r = a - q * b;
       
Return: /* Prepare for return. */
       *q_ = q;
       *r_ = r;
       return;
}
