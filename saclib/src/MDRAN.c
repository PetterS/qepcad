/*======================================================================
                      a <- MDRAN(m)

Modular digit, random.  

Inputs
  m : a positive BETA-digit. 

Outpus
  a : a random element of Z_m.
======================================================================*/
#include "saclib.h"

Word MDRAN(m)
       Word m;
{
       Word a,a1,a2,d1,d2,t;
       /* hide algorithm */

Step1: /* Compute. */
       d1 = ABS(DRAN());
       DPR(d1,m,&a,&t);
       if (m <= DELTA)
         goto Return;
       a1 = a;
       d2 = ABS(DRAN());
       DPR(d2,m,&a,&a2);
       if (a1 + a2 >= BETA)
         a = a + 1;

Return: /* Prepare for return. */
       return(a);
}
