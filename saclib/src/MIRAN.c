/*======================================================================
                      R <- MIRAN(M)

Modular integer, random.  

Inputs
  M : a positive integer.  

Outputs
  R : a uniformly distributed random element of Z_M.
======================================================================*/
#include "saclib.h"

Word MIRAN(M)
       Word M;
{
       Word R;

Step1: /* Compute. */
       R = MIHOM(M,IRAND(ILOG2(M) + ZETA));

Return: /* Prepare for return. */
       return(R);
}
