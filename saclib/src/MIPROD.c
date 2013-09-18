/*======================================================================
                      C <- MIPROD(M,A,B)

Modular integer product.  

Inputs
  M   : a positive integer.  
  A,B : elements of Z_M.

Outputs
  C   : A * B.
======================================================================*/
#include "saclib.h"

Word MIPROD(M,A,B)
       Word M,A,B;
{
       Word C;

Step1: /* Compute. */
       C = IREM(IPROD(A,B),M);

Return: /* Prepare for return. */
       return(C);
}
