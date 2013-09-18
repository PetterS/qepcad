/*===========================================================================
			     C <- IPROD3X3(A,B)

Integer product - 3x3-multiplication.

Inputs
  A, B : integers of length 3.

Outputs
  C    : an integer. C = A * B.
===========================================================================*/
#include "saclib.h"

Word IPROD3X3(A,B)
       Word A,B;
{
       Word a0,a1,a2;
       Word b0,b1,b2;
       Word s;
       Word c001,c010,c011,c020,c021;
       Word c100,c101,c110,c111,c120,c121;
       Word c200,c201,c210,c211,c220,c221;
       Word c1,c2,c3,c4,c5;
       Word Ch[6];
       Word C;

Step1: /* Read digits. */
       FIRST3(A,&a0,&a1,&a2);
       FIRST3(B,&b0,&b1,&b2);
       if (a2 < 0)
         {
         s = -1;
         a0 = -a0;
         a1 = -a1;
         a2 = -a2;
         }
       else
         s = 1;
       if (b2 < 0)
         {
         s = -s;
         b0 = -b0;
         b1 = -b1;
         b2 = -b2;
         }

Step2: /* Compute digit products. */
       DPR(a0,b0,&c001,&Ch[0]);
       DPR(a0,b1,&c011,&c010);
       DPR(a0,b2,&c021,&c020);

       DPR(a1,b0,&c101,&c100);
       DPR(a1,b1,&c111,&c110);
       DPR(a1,b2,&c121,&c120);

       DPR(a2,b0,&c201,&c200);
       DPR(a2,b1,&c211,&c210);
       DPR(a2,b2,&c221,&c220);

Step3: /* Add digit products. */

       /* Note that cxx0 <= BETA-1, cxx1 <= BETA-2. */
       c1 = c001 + c100 + c010;
       Ch[1] = c1 & BETA1;
       c2 = c1 >> ZETA;

       /* Note that c2 <= 2. */
       c2 = c2 + c101 + c011 + c200;
       c3 = c2 >> ZETA;
       c2 = c2 & BETA1;
       c2 = c2 + c110 + c020;
       Ch[2] = c2 & BETA1;
       c2 = c2 >> ZETA;
       c3 = c3 + c2;

       /* Note that c3 <= 4. */
       c3 = c3 + c201 + c111 + c021;
       c4 = c3 >> ZETA;
       c3 = c3 & BETA1;
       c3 = c3 + c210 + c120;
       Ch[3] = c3 & BETA1;
       c3 = c3 >> ZETA;
       c4 = c4 + c3;

       /* Note that c4 <= 4. */
       c4 = c4 + c211 + c121 + c220;
       Ch[4] = c4 & BETA1;
       c5 = c4 >> ZETA;

       Ch[5] = c5 + c221;
       /* Note that Ch[5] <= BETA - 1. */

Step4: /* Construct list. */
       C = IFATL(Ch,6,s);

Return: /* Prepare for return. */
       return(C);
}
