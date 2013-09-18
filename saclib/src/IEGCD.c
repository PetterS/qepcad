/*===========================================================================
                      IEGCD(a,b; c,u1,v1)

Integer extended greatest common divisor algorithm.

Inputs
  a,b : in Z.

Outputs
  c     : gcd(a,b)
  u1,v1 : in Z such that a * u1 + b * v1 = c.
          If a /= 0 and b /= 0 then 
             abs(u1) <= abs(b)/(2*c),
             abs(v1) <= abs(a)/(2*c).
          Otherwise 
             u1 = sign(a),
             v1 = sign(b).
===========================================================================*/
#include "saclib.h"

void IEGCD(a,b, c_,u1_,v1_)
       Word a,b, *c_,*u1_,*v1_;
{
       Word c,u1,v1;

Step1: /* Compute. */
       IHEGCD(a,b,&c,&v1);
       if (a == 0)
	  u1 = 0;
       else
	  u1 = IEQ(IDIF(c,IPROD(b,v1)),a);

Return: /* Prepare for return. */
       *c_ = c;
       *u1_ = u1;
       *v1_ = v1;
       return;
}
