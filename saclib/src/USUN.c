/*===========================================================================
			      C <- USUN(A,B)

Unordered set union.

Inputs
  A,B : unordered lists of objects.
        (A, B represent sets of objects.)

Outputs
  C   : unordered list representing the union of the sets A and B.
===========================================================================*/
#include "saclib.h"

Word USUN(A,B)
       Word A,B;
{
       Word C;

Step1: /* Compute. */
       C = CONC(USDIFF(A,B),B);

Return: /* Prepare for return. */
       return(C);
}
