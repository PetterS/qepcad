/*==========================================================================
                      C <- MIQ(M,A,B)

Modular integer quotient.  

Inputs
  M    : a positive integer.  
  A,B  : elements of Z_M,  B a unit of Z_M.

Outputs
  C    : A/B.
==========================================================================*/
#include "saclib.h"

Word MIQ(M,A,B)
       Word M,A,B;
{
       Word C;

Step1: /* Compute. */
       C = MIPROD(M,A,MIINV(M,B));

Return: /* Prepare for return. */
       return(C);
}
