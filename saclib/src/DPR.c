/*============================================================================
                      DPR(A,B; c1,c0)

Digit product.  

Inputs
  A, B : BETA-digits.  

Outputs
  c1, c0 : the unique BETA-digits such that a * b = c1 * BETA + c0,
           with c1 * c0 >= 0.

============================================================================*/
#include "saclib.h"

void DPR(A,B,c1_,c0_)
     Word A,B,*c1_, *c0_;
{
     DWord C;

     C = A;
     C = C*B;
     if (C < 0) {
       C = -C;
       *c0_ = (Word)(-(C & (BETA - 1)));
       *c1_ = (Word)(-(C >> ZETA)); }
     else {
       *c0_ = (Word)(C & (BETA - 1));
       *c1_ = (Word)(C >> ZETA); }
     
     return;
}
