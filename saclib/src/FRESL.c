/*======================================================================
                      FRESL(n; m,L)

Fermat residue list.

Inputs
  n  : a positive integer with no prime divisors less than 17.

Outputs
 m  : a positive BETA-digit.
 L  : an ordered list of the elements of Z(m) such that
      if x^2-n is a square then x is congruent to a (modulo m) for some a in L.
======================================================================*/
#include "saclib.h"

void FRESL(n, m_,L_)
       Word n, *m_,*L_;
{
       Word H,L,L1,M,a1,a2,a3,a4,b1,h,k,k1,m,m1;
       /* hide a1,a2,a3,a4,b1,h,k,k1,m,m1; */

Step1: /* Modulus 2^5. */
       a1 = IDREM(n,32);
       a2 = REM(a1,16);
       a3 = REM(a2,8);
       a4 = REM(a3,4);
       if (a4 == 3)
         {
         m = 4;
         if (a3 == 3)
           b1 = 2;
         else
           b1 = 0;
         }
       else
         if (a3 == 1)
           {
           m = 8;
           if (a2 == 1)
             b1 = 1;
           else
             b1 = 3;
           }
         else
           {
           m = 16;
           switch (a1 / 8)
             {
             case 0:
               b1 = 3;
               break;
             case 1:
               b1 = 7;
               break;
             case 2:
               b1 = 5;
               break;
             case 3:
               b1 = 1;
               break;
             }
           }
       if (m == 4)
         L = LIST1(b1);
       else
         L = LIST2(b1,m - b1);
       k = LENGTH(L);

Step2: /* Modulus 3^3. */
       a1 = IDREM(n,27);
       a2 = REM(a1,3);
       if (a2 == 2)
         {
         m1 = 3;
         k1 = 1;
         L1 = LIST1(0);
         }
       else
         {
         m1 = 27;
         k1 = 4;
         L1 = FRLSM(m1,a1);
         }

Step3: /* Combine. */
       L = MDLCRA(m,m1,L,L1);
       m = m * m1;
       k = k * k1;

Step4: /* Modulus 5^2. */
       a1 = IDREM(n,25);
       a2 = REM(a1,5);
       if (a2 == 2 || a2 == 3)
         {
         m1 = 5;
         L1 = LIST2(a2 - 1,6 - a2);
         k1 = 2;
         }
       else
         {
         m1 = 25;
         L1 = FRLSM(m1,a1);
         k1 = 7;
         }

Step5: /* Combine. */
       if (m1 >= BETA / m)
         goto Return;
       k = k * k1;
       L = MDLCRA(m,m1,L,L1);
       m = m * m1;

Step6: /* Moduli 7,11,13. */
       M = LIST3(7,11,13);
       H = LIST3(64,48,0);
       do
         {
         ADV(M,&m1,&M);
         if (m1 >= BETA / m)
           goto Return;
         a1 = IDREM(n,m1);
         L1 = FRLSM(m1,a1);
         k1 = LENGTH(L1);
         L = MDLCRA(m,m1,L,L1);
         m = m * m1;
         k = k * k1;
         ADV(H,&h,&H);
         if (k > h)
           goto Return;
         }
       while (1);

Return: /* Prepare for return. */
       *m_ = m;
       *L_ = L;
       return;
}
