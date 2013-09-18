/*===========================================================================
			 IDEGCD(a,b; c,u1,v1,u2,v2)

Integer doubly extended greatest common divisor algorithm.

Inputs
  a, b : in Z.

Outputs
  c      : gcd(a,b).
  u1,v1  : in Z such that  a * u1 + b * v1 = c.
  u2, v2 : in Z such that a * u2 + b * v2 = 0.
           If a /= 0 and b /= 0 then 
              abs(u1) <= abs(b)/(2*c),
              abs(v1) <= abs(a)/(2*c), 
              u2 = -b/c and v2=a/c.
           Otherwise 
              u1 = v2 = sign(a), 
              v1 = sign(b),
              u2 = -sign(b).
===========================================================================*/
#include "saclib.h"

void IDEGCD(a,b, c_,u1_,v1_,u2_,v2_)
       Word a,b, *c_,*u1_,*v1_,*u2_,*v2_;
{
       Word c,u1,u2,v1,v2;

Step1: /* Compute. */
       IEGCD(a,b,&c,&u1,&v1);
       if (c == 0) {
	  u2 = 0;
	  v2 = 0; }
       else {
	  u2 = INEG(IEQ(b,c));
	  v2 = IEQ(a,c); }

Return: /* Prepare for return. */
       *c_ = c;
       *u1_ = u1;
       *v1_ = v1;
       *u2_ = u2;
       *v2_ = v2;
       return;
}
