/*============================================================================
                      DPRNN(a,b; c1,c0)

Digit product.  

Inputs
  a, b : nonnegative BETA-digits.  

Outputs
  c1, c0 : the unique nonnegative BETA-digits such that a * b = 
           c1 * BETA + c0.

Note: This program assumes that BETA = 2^29.
============================================================================*/
#include "saclib.h"

void DPRNN(a,b, c1_,c0_)
       Word a,b, *c1_,*c0_;
{
       BDigit a0,a1,b0,b1,c0,c1,d0,d1,dp,p0,p1,p10,p11,p2;

const  BDigit
        m15 = (1 << 15) - 1,
        m29 = (1 << 29) - 1,
        m30 = (1 << 30) - 1;

Step1: /* Break apart the inputs. */
        a0 = a & m15;
        a1 = a >> 15;
        b0 = b & m15;
        b1 = b >> 15;

Step2: /* Multiply the parts. */
       p0 = a0 * b0;
       p1 = a1 * b0 + a0 * b1;
       p2 = a1 * b1;

Step3: /* Add the products in base 2^30. */
        p10 = p1 & m15;
        p11 = p1 >> 15;
        d0 = p0 + (p10 << 15);
        dp = d0 >> 30;
        d0 = d0 & m30;
        d1 = p2 + p11 + dp;

Step4: /* Convert to base 2^29. */
        c0 = d0 & m29;
        dp = d0 >> 29;
        c1 = (d1 << 1) | dp;

Return: /* Return c1 and c0. */
        *c1_ = c1;
        *c0_ = c0;
        return;
}


