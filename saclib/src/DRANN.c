/*======================================================================
                      a <- DRANN()

Digit, random non-negative.

Outputs
  a  : random non-negative BETA-digit.
       Caution, the low-order bits of a are not very random.
======================================================================*/
#include "saclib.h"

Word DRANN()
{
       Word a,t;
       /* hide algorithm */

Step1: /* Compute. */
       DPR(RTERM,RMULT,&t,&a);
       a = a + RINC;
       if (a >= BETA)
         a = a - BETA;
       RTERM = a;

Return: /* Prepare for return. */
       return(a);
}
