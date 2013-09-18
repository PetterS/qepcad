/*======================================================================
                      a <- AFFRN(R)

Algebraic number field element from rational number.  

Inputs
  R : in Q.

Outputs
  a : in Q(alpha). a = R represented as an element of Q(alpha).
======================================================================*/
#include "saclib.h"

Word AFFRN(R)
       Word R;
{
       Word a;

Step1: /* Convert. */
       if (R == 0)
         a = 0;
       else
         a = LIST2(R,PMON(1,0));

Return: /* Prepare for return. */
       return(a);
}
