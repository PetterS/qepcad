/*===========================================================================
			       T <- ACLOCK()

Clock minus garbage collection time.

Outputs
  T : a C integer, the system clock time minus garbage collection
      time in milliseconds.
===========================================================================*/
#include "saclib.h"

Word ACLOCK()
{
       Word T;

Step1: /* Compute. */
       T = CLOCK() - TAU;

Return: /* Prepare for return. */
       return(T);
}
