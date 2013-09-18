/*======================================================================
                      FPCATCH()

Floating-point catch.

Side Effects
  This function clears the current record of floating-point exceptions,
  so that subsequent calls to FPCHECK will check for floating-point
  underflow, overflow, and divide-by-zero that occurred after this call.
======================================================================*/
#include "saclib.h"
#include <fenv.h>

void FPCATCH() 
{ 
     feclearexcept(FE_ALL_EXCEPT);

Return: /* Prepare to return. */
      return;
}

