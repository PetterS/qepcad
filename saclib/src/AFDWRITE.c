/*===========================================================================
                         AFDWRITE(M,I,b,n)

Algebraic number field, decimal write.  

Inputs
  M : integral minimal polynomial for a real algebraic number alpha.
  I : an acceptable isolating interval for alpha.
  b : an element of Q(alpha).
  n : non-negative integer.

Side effects
    A decimal approximation to b is written to the output stream.
    |b - R| < 1/2 10^{-n}.  The decimal approximation is followed by
    '+' if |R| < |b| and '-' if |R| < |b|.
===========================================================================*/
#include "saclib.h"

void AFDWRITE(M,I,b,n)

       Word M,I,b,n;
{
       Word J,N;

Step1: /* Convert to algebraic number and write. */
       ANFAF(M,I,b,&N,&J);
       ANDWRITE(N,J,n);

Return: /* Prepare for return. */
       return;
}
