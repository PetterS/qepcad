/*======================================================================
                      S <- RNNEG(R)

Rational number negative.  

Inputs
  R : a rational number.  

Outputs
  S : -R.
======================================================================*/
#include "saclib.h"

Word RNNEG(R)
       Word R;
{
       Word R1,Rp,Rp1,S;
       /* hide R1,Rp,S; */

Step1: /* Compute. */
       if (R == 0)
         S = 0;
       else
         {
         ADV(R,&R1,&Rp);
         Rp1 = INEG(R1);
         S = COMP(Rp1,Rp);
         }

Return: /* Prepare for return. */
       return(S);
}
