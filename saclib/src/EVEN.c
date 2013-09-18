/*======================================================================
<macro>               t <- EVEN(a)

EVEN.  

Inputs
  a : a C integer.  

Outputs
  t  : t = 1 if a is even and 
       t = 0 otherwise.
======================================================================*/
#ifndef NO_SACLIB_MACROS
#define NO_SACLIB_MACROS
#endif
#include "saclib.h"

Word EVEN(a)
       Word a;
{
       Word t;

Step1: /* Compute. */
       t = REM(a,2);
       if (t < 0)
	  t = 0;
       else
	  t = 1 - t;

Return: /* Prepare for return. */
       return(t);
}
