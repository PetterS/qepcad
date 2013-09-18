/*======================================================================
                      t <- CLOCK()

Clock.

Outputs
  t :  the system clock time in milliseconds.
======================================================================*/
#include "saclib.h"
#include <time.h>

Word CLOCK()
{
       Word t;
       /* hide t; */

Step1: /* Get the system time. */
       /* Ticks per millisec. = ticks * 1000 / ticks per sec. */
       t = (int)clock() * 1000 / CLK_TCK;

Return: /* Prepare for return. */
       return(t);
}
