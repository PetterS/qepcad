/*===========================================================================
			     C <- IPROD2X2(A,B)

Integer product - 2x2-multiplication.

Inputs
  A, B : integers of length 2.

Outputs
  C    : an integer. C = A * B.
===========================================================================*/
#include "saclib.h"

Word IPROD2X2(A,B)
       Word A,B;
{
       Word a0,a1;
       Word b0,b1;
       Word s;
       Word c001;
       Word c100,c101;
       Word c010,c011;
       Word c110,c111;
       Word c1,c2,c3;
       Word Ch[4];
       Word C;

Step1: /* Read digits. */
       FIRST2(A,&a0,&a1);
       FIRST2(B,&b0,&b1);
       if (a1 < 0)
         {
         s = -1;
         a0 = -a0;
         a1 = -a1;
         }
       else
         s = 1;
       if (b1 < 0)
         {
         s = -s;
         b0 = -b0;
         b1 = -b1;
         }

Step2: /* Compute digit products. */
       DPR(a0,b0,&c001,&Ch[0]);
       DPR(a0,b1,&c011,&c010);
       DPR(a1,b0,&c101,&c100);
       DPR(a1,b1,&c111,&c110);

Step3: /* Add digit products. */
       c1 = c001 + c100 + c010;
       Ch[1] = c1 & BETA1;
       c2 = c1 >> ZETA;

       /* Note that c2 <= 2. */
       c2 = c2 + c101 + c011 + c110;
       Ch[2] = c2 & BETA1;
       c3 = c2 >> ZETA;

       Ch[3] = c3 + c111;
       /* Note that Ch[3] <= BETA - 1. */

Step4: /* Construct list. */
       C = IFATL(Ch,4,s);

Return: /* Prepare for return. */
       return(C);
}
