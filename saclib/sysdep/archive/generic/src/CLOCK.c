/*======================================================================
                      t <- CLOCK()

Clock.

Outputs
  t :  the system clock time in milliseconds.
======================================================================*/
#include "saclib.h"
#include <sys/time.h>

Word CLOCK()
{
       Word t;
       /* hide t; */

Step1: /* Get the system time. */
       t = (Word)time(NULL)*1000;

Return: /* Prepare for return. */
       return(t);
}
