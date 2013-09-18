/*======================================================================
                      Q <- PARTN(n,P)

Partition, next.

Inputs
  n : a BETA-digit, n > 0.
  P : a partition of n.

Outputs
  Q : the next partition of n after P in lexicographical order,
      if any.  Otherwise Q=().
======================================================================*/
#include "saclib.h"

Word PARTN(n,P)
       Word n,P;
{
       Word Pp,Q,a,ap,b,i,q,r;
       /* hide Pp,a,ap,b,i,q,r; */

Step1: /* r=1. */
       r = LENGTH(P);
       if (r == 1)
         {
         Q = NIL;
         goto Return;
         }

Step2: /* r >= 2. */
       Q = NIL;
       Pp = P;
       for (i = 1; i <= r - 2; i++)
         {
         ADV(Pp,&a,&Pp);
         Q = COMP(a,Q);
         }
       a = FIRST(Pp);
       b = SECOND(Pp);
       ap = a + 1;
       QREM(a + b,ap,&q,&r);
       for (i = 1; i <= q - 1; i++)
         Q = COMP(ap,Q);
       Q = COMP(ap + r,Q);
       Q = INV(Q);

Return: /* Prepare for return. */
       return(Q);
}
