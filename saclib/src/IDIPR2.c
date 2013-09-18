/*======================================================================
                      C <- IDIPR2(A,B,a,b)

Integer digit inner product, length 2.

Inputs
  A, B  : in Z.
  a, b  : BETA-digits.

Outputs
  C : A * a + B * b.
======================================================================*/
#include "saclib.h"

Word IDIPR2(A,B,a,b)
       Word A,B,a,b;
{
       Word C;

Step1: /* Compute. */
       C = ISUM(IDPR(A,a),IDPR(B,b));

Return: /* Prepare for return. */
       return(C);
}
