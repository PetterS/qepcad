/*======================================================================
                      a <- DRAN()

Digit, random.

Outputs
 a  : random BETA-digit.
======================================================================*/
#include "saclib.h"

Word DRAN()
{
       Word a,a1,a2,s;
       /* hide algorithm */

Step1: /* Compute. */
       a1 = DRANN();
       s = 0;
       a1 = a1 + a1;
       if (a1 >= BETA)
         {
         s = 1;
         a1 = a1 - BETA;
         }
       a1 = a1 / DELTA;
       a2 = DRANN();
       a2 = a2 / EPSIL;
       a = a1 * DELTA + a2;
       if (s == 1)
         a = -a;

Return: /* Prepare for return. */
       return(a);
}
