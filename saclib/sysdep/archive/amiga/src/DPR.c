/*============================================================================
                      DPR(a,b; c1,c0)

Digit product.  

Inputs
  a, b : BETA-digits.  

Outputs
  c1, c0 : the unique BETA-digits such that a * b = c1 * BETA + c0,
           with c1 * c0 >= 0.

Note: This program assumes that BETA = 2^29.
============================================================================*/
#include "saclib.h"

void DPR(a,b, c1_,c0_)
       Word a,b, *c1_,*c0_;
{
       BDigit a0,a1,ap,b0,b1,bp,c0,c1,d0,d1,dp,p0,p1,p10,p11,p2,s;

const  BDigit
         m15 = (1 << 15) - 1,
         m29 = (1 << 29) - 1,
         m30 = (1 << 30) - 1;

Step1: /* Compute absolute values of inputs. */
        s = 1;
        if (a < 0) {
           ap = -a;
           s = -s; }
        else
           ap = a;
        if (b < 0) {
           bp = -b;
           s = -s; }
        else 
           bp = b;

Step2: /* Break apart the inputs. */
        a0 = ap & m15;
        a1 = ap >> 15;
        b0 = bp & m15;
        b1 = bp >> 15;

Step3: /* Multiply the parts. */
        p0 = a0 * b0;
        p1 = a1 * b0 + a0 * b1;
        p2 = a1 * b1;

Step4: /* Add the products in base 2^30. */
        p10 = p1 & m15;
        p11 = p1 >> 15;
        d0 = p0 + (p10 << 15);
        dp = d0 >> 30;
        d0 = d0 & m30;
        d1 = p2 + p11 + dp;

Step5: /* Convert to base 2^29. */
        c0 = d0 & m29;
        dp = d0 >> 29;
        c1 = (d1 << 1) | dp;

Step6: /* Give correct signs to c1 and c0. */
        if (s < 0) {
           c1 = -c1;
           c0 = -c0; }

Return: /* Return c1 and c0. */
        *c1_ = c1;
        *c0_ = c0;
        return;
}
