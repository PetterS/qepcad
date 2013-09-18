/*======================================================================
                      t <- CLOCK()

Clock.

Outputs
  t :  the system clock time in milliseconds.
======================================================================*/
#include "saclib.h"
#include <sys/types.h>
#include <sys/times.h>
#include <sys/param.h>

Word CLOCK()
{
       Word t;
       struct tms a;
       /* hide t; */

Step1: /* Get the system time. */
       times(&a);
       t = a.tms_utime * 1000 / HZ;

Return: /* Prepare for return. */
       return(t);
}
