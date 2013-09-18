/*======================================================================
                      b <- BITRAN()

Bit, random.

Outputs
  b  : a random bit, 0 or 1.
======================================================================*/
#include "saclib.h"

Word BITRAN()
{
       Word a,b;
       /* hide algorithm */

Step1: /* Compute a random bit. */
       a = DRANN();
       a = a + a;
       if (a >= BETA)
         b = 1;
       else
         b = 0;
       goto Return;

Return: /* Prepare for return. */
       return(b);
}
