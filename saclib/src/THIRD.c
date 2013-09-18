/*======================================================================
                      a <- THIRD(L)

Third.

Inputs
  L  : list of length 3 or more.

Outputs
  a  : the third element of L.
======================================================================*/
#include "saclib.h"

Word THIRD(L)
       Word L;
{
       Word a;
       /* hide algorithm */

Step1: /* Get it. */
       a = FIRST(RED2(L));

Return: /* Prepare for return. */
       return(a);
}
