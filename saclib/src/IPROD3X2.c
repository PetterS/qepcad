/*===========================================================================
			     C <- IPROD3X2(A,B)

Integer product - 3x2-multiplication.

Inputs
  A    : an integer of length 3.
  B    : an integer of length 2.

Outputs
  C    : an integer. C = A * B.
===========================================================================*/
#include "saclib.h"

Word IPROD3X2(A,B)
       Word A,B;
{
       Word a0,a1,a2;
       Word b0,b1;
       Word s;
       Word c001,c010,c011;
       Word c100,c101,c110,c111;
       Word c200,c201,c210,c211;
       Word c1,c2,c3,c4;
       Word Ch[5];
       Word C;

Step1: /* Read digits. */
       FIRST3(A,&a0,&a1,&a2);
       FIRST2(B,&b0,&b1);
       if (a2 < 0)
         {
         s = -1;
         a0 = -a0;
         a1 = -a1;
         a2 = -a2;
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

       DPR(a2,b0,&c201,&c200);
       DPR(a2,b1,&c211,&c210);

Step3: /* Add digit products. */
       c1 = c001 + c100 + c010;
       Ch[1] = c1 & BETA1;
       c2 = c1 >> ZETA;

       /* Note that c2 <= 2. */
       c2 = c2 + c101 + c011 + c200;
       c3 = c2 >> ZETA;
       c2 = c2 & BETA1;
       c2 = c2 + c110;
       Ch[2] = c2 & BETA1;
       c2 = c2 >> ZETA;
       c3 = c3 + c2;

       /* Note that c3 <= 3. */
       c3 = c3 + c201 + c111 + c210;
       Ch[3] = c3 & BETA1;
       c4 = c3 >> ZETA;

       Ch[4] = c4 + c211;
       /* Note that Ch[4] <= BETA - 1. */

Step4: /* Construct list. */
       C = IFATL(Ch,5,s);

Return: /* Prepare for return. */
       return(C);
}
