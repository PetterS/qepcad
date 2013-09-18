/*======================================================================
                      a <- FOURTH(L)

Fourth.

Inputs
  L  : list of length 4 or more.

Outputs
  a  : the fourth element of L.
======================================================================*/
#include "saclib.h"

Word FOURTH(L)
       Word L;
{
       Word a;
       /* hide algorithm */

Step1: /* Get it. */
       a = FIRST(RED3(L));

Return: /* Prepare for return. */
       return(a);
}
