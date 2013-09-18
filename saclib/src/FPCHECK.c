/*======================================================================
                      FPCHECK()

Floating-point check.

Outputs
  t : 1 if a floating-point underflow, overflow, or divide by zero
  has occurred since the last call to FPCATCH(); 0 otherwise.
======================================================================*/

#include "saclib.h"
#include <fenv.h>

Word FPCHECK()
{
  Word t;

  t = 0;
  if (fetestexcept(FE_DIVBYZERO | FE_UNDERFLOW | FE_OVERFLOW | FE_INVALID)) {
    t = 1;
  }

  return t;
}
