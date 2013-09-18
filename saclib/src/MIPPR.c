/*======================================================================
                      C <- MIPPR(r,M,A,B)

Modular integral polynomial product.

Inputs
  M    : in Z, M > 0.
  A, B : in Z/(M)[X1,...,Xr].
  r    : a BETA-digit, r >= 0, the number of variables.

Outputs
  C    : in Z/(M)[X1,...,Xr], C = A * B.
======================================================================*/
#include "saclib.h"

Word MIPPR(r,M,A,B)
       Word r,M,A,B;
{
       Word C;

Step1: /* Compute. */
       C = MIPHOM(r,M,IPPROD(r,A,B));

Return: /* Prepare for return. */
       return(C);
}
