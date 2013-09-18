/*======================================================================
                      A <- PARTSS(p)

Partition sumset.

Inputs
  p : a partition.

Outputs
  A : the sum set of p, a characteristic set.
======================================================================*/
#include "saclib.h"

Word PARTSS(p)
       Word p;
{
       Word A,B,a,pp;
       /* hide a,pp; */

Step1: /* Compute. */
       A = 1;
       pp = p;
       while (pp != NIL)
         {
         ADV(pp,&a,&pp);
         B = IMP2(A,a);
         A = CSUN(A,B);
         }

Return: /* Prepare for return. */
       return(A);
}
