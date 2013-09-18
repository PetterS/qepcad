/*======================================================================
                      C <- VIDIF(A,B)

Vector of integers difference.

Inputs
 A,B : n-vectors over Z.

Outputs
  C  : an n-vector over Z, C = A-B.
======================================================================*/
#include "saclib.h"

Word VIDIF(A,B)
       Word A,B;
{
       Word C;

Step1: /* Compute. */
       C = VISUM(A,VINEG(B));

Return: /* Prepare for return. */
       return(C);
}
