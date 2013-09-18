/*===========================================================================
                             Ap <- MIPMON(r,M,A)

Modular integral polynomial monic.

Inputs
  r : a BETA-digit, r >= 1, the number of variables;
  M : in Z, M > 1.
  A : in Z/(M)[X1,...,Xr].  A = 0 or lbcf(A) is a unit in Z/(M).

Outputs
  Ap : in Z/(M)[X1,...,Xr].
       If A is non-zero then Ap is the polynomial similar to A
       with lbcf(Ap) = 1.  If A = 0 then Ap = 0.
===========================================================================*/
#include "saclib.h"

Word MIPMON(r,M,A)
       Word r,M,A;
{
       Word Ap,a,ap;

Step1: /* A = 0. */
       if (A == 0) {
          Ap = 0;
          goto Return; }

Step2: /* A non-zero. */
       a = PLBCF(r,A);
       ap = MIINV(M,a);
       Ap = MIPMIP(r,M,ap,A);

Return: /* Prepare for return. */
       return(Ap);
}
