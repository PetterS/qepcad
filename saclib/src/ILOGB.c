/*======================================================================
                      n <- ILOGB(A)

Integer logarithm, base BETA.

Inputs
  A : in Z.

Outputs
  n : a BETA-integer.
      If A = 0 then n = 0.
      Otherwise   n = floor(log_BETA(|A|)) + 1,
======================================================================*/
#include "saclib.h"

Word ILOGB(A)
       Word A;
{
       Word n;

Step1: /* A single-precision. */
       if (A < BETA) {
         if (A == 0)
           n = 0;
         else
           n = 1;
         goto Return; }

Step2: /* A multiple-precision. */
       n = LENGTH(A);

Return: /* Prepare for return. */
       return(n);
}
