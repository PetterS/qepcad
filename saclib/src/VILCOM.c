/*======================================================================
                      C <- VILCOM(a,b,A,B)

Vector of integers linear combination.

Inputs
  a,b : in Z.
  A,B : n-vectors over Z.

Outputs
  C   : an n-vector over Z, C = aA+bB.
======================================================================*/
#include "saclib.h"

Word VILCOM(a,b,A,B)
       Word a,b,A,B;
{
       Word C,S,T;
       /* hide C; */

Step1: /* Compute. */
       S = VISPR(a,A);
       T = VISPR(b,B);
       C = VISUM(S,T);

Return: /* Prepare for return. */
       return(C);
}
