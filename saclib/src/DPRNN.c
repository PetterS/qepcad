/*============================================================================
                      DPRNN(A,B; c1,c0)

Digit product.  

Inputs
  A, B : nonnegative BETA-digits.  

Outputs
  c1, c0 : the unique nonnegative BETA-digits such that a * b = 
           c1 * BETA + c0.

============================================================================*/
#include "saclib.h"

void DPRNN(A,B,c1_,c0_)
     Word A,B,*c1_, *c0_;
{
     DWord C;

     C = A;
     C = C*B;
     *c0_ = (Word)(C & (BETA - 1));
     *c1_ = (Word)(C >> ZETA);

     return;
}
