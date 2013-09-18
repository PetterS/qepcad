/*======================================================================
                      t <- RNCOMP(R,S)

Rational number comparison.  

Inputs
  R, S : rational numbers.

Outpus
  t    : sign(R-S).
======================================================================*/
#include "saclib.h"

Word RNCOMP(R,S)
       Word R,S;
{
       Word R1,R2,S1,S2,r,s,t;
       /* hide R1,R2,S1,S2,r,s,t; */

Step1: /* R or S zero. */
       if (R == 0)
         {
         t = -RNSIGN(S);
         goto Return;
         }
       if (S == 0)
         {
         t = RNSIGN(R);
         goto Return;
         }

Step2: /* Opposite signs. */
       FIRST2(R,&R1,&R2);
       FIRST2(S,&S1,&S2);
       r = ISIGNF(R1);
       s = ISIGNF(S1);
       t = (r - s) / 2;
       if (t != 0)
         goto Return;

Step3: /* Same sign. */
       t = ICOMP(IPROD(R1,S2),IPROD(R2,S1));

Return: /* Prepare for return. */
       return(t);
}
