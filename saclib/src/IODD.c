/*======================================================================
                      t <- IODD(A)

Integer odd.  

Inputs
  A : in Z.

Outputs
  t : If A is odd then t = 1 and otherwise t = 0.
======================================================================*/
#include "saclib.h"

Word IODD(A)
       Word A;
{
       Word t;
       /* hide algorithm */

Step1: /* Determine. */
       if (A < BETA)
         t = ODD(A);
       else
         t = ODD(FIRST(A));

Return: /* Prepare for return. */
       return(t);
}
