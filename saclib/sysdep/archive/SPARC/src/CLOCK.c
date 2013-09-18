/*======================================================================
                      t <- CLOCK()

Clock.

Outputs
  t :  the system clock time in millisecconds. For 60 Hz cpu-clock.
======================================================================*/
#include "saclib.h"
#include <sys/types.h>
#include <sys/times.h>

Word CLOCK()
{
       Word t;
       struct tms a;
       /* hide t; */

Step1: /* Get the system time. */
       times(&a);
       t = a.tms_utime * 100 / 6;

Return: /* Prepare for return. */
       return(t);
}
