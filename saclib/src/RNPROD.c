/*======================================================================
                      T <- RNPROD(R,S)

Rational number product.  

Inputs
  R,S : rational numbers.  

Outputs
 T    : R * S.
======================================================================*/
#include "saclib.h"

Word RNPROD(R,S)
       Word R,S;
{
       Word D1,D2,R1,R2,Rb1,Rb2,S1,S2,Sb1,Sb2,T,T1,T2;
       /* hide R1,R2,S1,S2,T; */

Step1: /* R=0 or S=0. */
       if (R == 0 || S == 0)
         {
         T = 0;
         goto Return;
         }

Step2: /* Obtain numerators and denominators. */
       FIRST2(R,&R1,&R2);
       FIRST2(S,&S1,&S2);

Step3: /* R and S integers. */
       if (R2 == 1 && S2 == 1)
         {
         T1 = IPROD(R1,S1);
         T = LIST2(T1,1);
         goto Return;
         }

Step4: /* R or S an integer. */
       if (R2 == 1)
         {
         IGCDCF(R1,S2,&D1,&Rb1,&Sb2);
         T1 = IPROD(Rb1,S1);
         T = LIST2(T1,Sb2);
         goto Return;
         }
       if (S2 == 1)
         {
         IGCDCF(S1,R2,&D2,&Sb1,&Rb2);
         T1 = IPROD(Sb1,R1);
         T = LIST2(T1,Rb2);
         goto Return;
         }

Step5: /* General case. */
       IGCDCF(R1,S2,&D1,&Rb1,&Sb2);
       IGCDCF(S1,R2,&D2,&Sb1,&Rb2);
       T1 = IPROD(Rb1,Sb1);
       T2 = IPROD(Rb2,Sb2);
       T = LIST2(T1,T2);

Return: /* Prepare for return. */
       return(T);
}
