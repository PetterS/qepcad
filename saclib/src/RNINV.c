/*======================================================================
                      S <- RNINV(R)

Rational number inverse.  

Inputs
  R : a non-zero rational number.  

Outputs
  S : 1/R.
======================================================================*/
#include "saclib.h"

Word RNINV(R)
       Word R;
{
       Word R1,R2,S,S1,S2;
       /* hide S; */

Step1: /* Compute. */
       FIRST2(R,&R1,&R2);
       if (ISIGNF(R1) > 0)
         {
         S1 = R2;
         S2 = R1;
         }
       else
         {
         S1 = INEG(R2);
         S2 = INEG(R1);
         }
       S = LIST2(S1,S2);

Return: /* Prepare for return. */
       return(S);
}
