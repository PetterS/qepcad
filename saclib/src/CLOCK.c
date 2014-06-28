/*======================================================================
                      t <- CLOCK()

Clock.

Outputs
  t :  the system clock time in millisecconds.
======================================================================*/
#include "saclib.h"

#ifndef _MSC_VER 
#include <sys/resource.h>

Word CLOCK()
{
       Word t;
       struct rusage r;
       struct timeval v;


Step1: /* Get the system time. */
       getrusage(RUSAGE_SELF, &r);
       v = r.ru_utime;
       t = v.tv_sec * 1000 + v.tv_usec / 1000;

Return: /* Prepare for return. */
       return(t);
}
#else
#include <time.h>
Word CLOCK()
{
	double seconds = (double)clock() / (double)CLOCKS_PER_SEC;
	return (Word)(seconds * 1000.0);
}
#endif
