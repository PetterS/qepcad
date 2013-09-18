/*======================================================================
                      DQR(a1,a0,b; q,r)

Digit quotient and remainder.  

Inputs
  a1, a0, b : BETA-integers with a1 * a0 >= 0 and abs(b) > abs(a1).  

Outputs
  q : a BETA-integer, the integral part of (a1 * BETA + a0) / b.
  r : a BETA-integer, (a1 * BETA + a0) - b * q.  
======================================================================*/
#include "saclib.h"

void DQR(a1,a0,b,q_,r_)
     Word  a1, a0, b, *q_, *r_;
{
     DWord N,T;

     N = a1;
     T = b;
     N <<= ZETA;
     N += a0;
     T = N / b;
     *q_ = (Word)(T);
     T *= b;
     N -= T;
     *r_ = (Word)(N);
     return;
}
