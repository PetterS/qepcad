/*======================================================================
                      A <- IRAND(n)

Integer, random.  

Inputs
  n : a positive BETA-integer.  

Outputs
  A : an integer with random sign 
      and random absolute value less than 2^n.
======================================================================*/
#include "saclib.h"

Word IRAND(n)
       Word n;
{
       Word A,a,i,q,r,s;
       /* hide a,i,q,r,s; */

Step1: /* Compute sign and high-order BETA-digit. */
       QREM(n,ZETA,&q,&r);
       if (r == 0)
         {
         q = q - 1;
         r = ZETA;
         }
       a = DRAN();
       s = SIGN(a);
       a = a / TABP2[ZETA - r + 1];
       if (q == 0)
         {
         A = a;
         goto Return;
         }
       A = NIL;
       if (a != 0)
         A = COMP(a,A);

Step2: /* Compute remaining digits. */
       for (i = 1; i <= q; i++)
         {
         a = ABS(DRAN());
         if (s < 0)
           a = -a;
         if (a != 0 || A != NIL)
           A = COMP(a,A);
         }
       if (A == NIL)
         A = 0;
       else
         if (RED(A) == NIL)
           A = FIRST(A);

Return: /* Prepare for return. */
       return(A);
}
