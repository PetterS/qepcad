/*======================================================================
<macro>               t <- ODD(a)

Odd.  

Inputs
  a : a C integer.  

Outpus
  t : t=1 if a is odd and t=0 otherwise.
======================================================================*/
#ifndef NO_SACLIB_MACROS
#define NO_SACLIB_MACROS
#endif
#include "saclib.h"

Word ODD(a)
       Word a;
{
       Word t;

Step1: /* Decide. */
       t = REM(a,2);
       if (t != 0)
	  t = 1;

Return: /* Prepare for return. */
       return(t);
}
