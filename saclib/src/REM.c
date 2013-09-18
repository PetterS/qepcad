/*==========================================================================
                      r <- REM(a,b)

Remainder.

Inputs
  a,b :  C integers, b /= 0.

Outputs
  r   :  a - q * b where q is the integral part of a / b.
==========================================================================*/
#include "saclib.h"

Word REM(a,b)
       Word a,b;
{
       Word q,r;

Step1: /* Use QREM */
       QREM(a,b,&q,&r);

Return: /* Prepare for return */
       return(r);
}    
